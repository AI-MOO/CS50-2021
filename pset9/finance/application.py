import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

    if db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY stock_symbol", user_id):
        actual_assets = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY stock_symbol", user_id)
        for row in range(len(actual_assets)):
            actual_assets[row]['total_price'] = usd(actual_assets[row]['total_price'])

        return render_template("index.html", actual_assets=actual_assets, user_cash=usd(user_cash))

    else:
        return render_template("index.html", user_cash=usd(user_cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        user_id = session["user_id"]

        stock_info = lookup(symbol)
        if not stock_info:
            return apology("Invalid Symbol", 400)

        stock_name = stock_info['name']
        stock_symbol = stock_info['symbol']
        stock_price = float(stock_info['price'])
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

        if not symbol:
            return apology("Missing Symbol", 400)

        elif not shares:
            return apology("Missing Shares", 400)

        elif not shares.isnumeric():
            return apology("Only Integers are accepted for shares!", 400)

        elif user_cash < int(shares) * float(stock_info['price']):
            return apology("Can't afford", 400)

        # update the cash of user after the buy transation
        total_shares_price = int(shares) * stock_price
        user_cash = user_cash - total_shares_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, user_id)

        # add a record for current transation
        db.execute("INSERT INTO trans_history (user_id, stock_symbol, shares, stock_price, tans_date) VALUES(?,?,?,?,datetime('now'))"
        ,user_id ,stock_symbol, shares, usd(stock_price))

        if db.execute("SELECT shares FROM transactions WHERE user_id= ? AND stock_symbol = ?", user_id, stock_symbol):
            db.execute("UPDATE transactions SET shares = shares + ?, total_price = total_price + ?, tans_date=datetime('now') WHERE user_id= ? AND stock_symbol= ?"
            ,shares, total_shares_price, user_id, stock_symbol)

        else:
            db.execute("INSERT INTO transactions (user_id, stock_symbol, stock_name, stock_price, shares, total_price, tans_date) VALUES(?,?,?,?,?,?,datetime('now'))"
            ,user_id ,stock_symbol ,stock_name , usd(stock_price) ,shares ,total_shares_price)


        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    if db.execute("SELECT * FROM trans_history WHERE user_id = ?", user_id):
        records = db.execute("SELECT * FROM trans_history WHERE user_id = ? ORDER BY tans_date", user_id)
        return render_template("history.html", records=records)

    else:
        return redirect("/history")



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing Symbol", 400)
        elif not lookup(symbol):
            return apology("Invalid Symbol", 400)
        stock_info = lookup(symbol)
        stock_name = stock_info['name']
        stock_symbol = stock_info['symbol']
        stock_price = usd(int(stock_info['price']))

        return render_template("quoted.html", stock_name=stock_name, stock_symbol=stock_symbol, stock_price=stock_price)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        elif not confirmation:
            return apology("must provide a confirmation password", 400)

        elif password != confirmation:
            return apology("passowrd and confirmation are not matched!", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("Username is already exist!", 400)

        db.execute("Insert INTO users (username, hash) VALUES(?,?)", username, generate_password_hash(password))
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    stocks_symbols = db.execute("SELECT stock_symbol FROM transactions WHERE user_id = ? ORDER BY stock_symbol", user_id)


    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        user_shares = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND stock_symbol = ?", user_id, stock_symbol)[0]['shares']

        # update the cash of user after the buy transation
        stock_info = lookup(stock_symbol)
        stock_price = float(stock_info['price'])
        total_shares_price = int(shares) * stock_price
        user_cash = user_cash + total_shares_price


        if stock_symbol == None:
            return apology("Missing Symbol", 400)

        if not shares:
            return apology("Missing Shares", 400)

        elif int(shares) > int(user_shares):
            return apology("Too Many Shares!", 400)

        elif int(shares) == int(user_shares):
            # add a record for current transation
            db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, user_id)
            db.execute("INSERT INTO trans_history (user_id, stock_symbol, stock_price, shares, tans_date) VALUES(?,?,?,?,datetime('now'))"
            ,user_id, stock_symbol, stock_price, -1 * int(shares))
            db.execute("DELETE From transactions WHERE user_id = ? AND stock_symbol = ?", user_id, stock_symbol)
            return redirect("/")


        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, user_id)

        # add a record for current transation
        db.execute("INSERT INTO trans_history (user_id, stock_symbol, stock_price, shares, tans_date) VALUES(?,?,?,?,datetime('now'))"
        ,user_id, stock_symbol, stock_price, -1 * int(shares))

        # Update the actual assests
        db.execute("UPDATE transactions SET shares = shares - ?, total_price = total_price - ?, tans_date=datetime('now') WHERE user_id= ? AND stock_symbol= ?"
        ,shares, total_shares_price, user_id, stock_symbol)
        return redirect("/")

    else:
        return render_template("sell.html", stocks_symbols=stocks_symbols)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)