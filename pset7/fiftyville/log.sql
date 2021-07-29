--01 Get the description of crime_scence report in 28/07/2020 at "Chamberlin Street"
SELECT description FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2020 AND street = "Chamberlin Street";

-- Result: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time —
-- each of their interview transcripts mentions the courthouse.


--02 Get the transcripts of the interviews which happened in the day of crime
SELECT transcript FROM interviews
WHERE day = 28 AND month = 7 AND year = 2020 AND transcript like "%courthouse%";

-- Result: Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse,
-- I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call,
-- I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 03 Get the possible activites
SELECT activity FROM courthouse_security_logs;
-- Results: either exit or entrance

-- 04 Get the names of suspects based on of license plates of car that exiting the courthouse within 10 minutes
SELECT name FROM people
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute >= 15 AND minute < 25 AND activity = "exit";
--Patrick, Ernest, Amber, Danielle, Roger, Elizabeth, Russell, Evelyn


-- 05 Get the names of suspects who made a withdrawal that day on Fifer Street
SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE day = 28 AND month = 7 AND year = 2020 AND transaction_type = "withdraw" AND atm_location = "Fifer Street";
-- Danielle, Bobby, Madison, Ernest, Roy, Elizabeth, Victoria, Russell

-- 06 Get the names of suspects who took the first flight on the 29th
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = "7" AND year = 2020
                   ORDER BY hour, minute LIMIT 1);
-- Doris, Roger, Ernest, Edward, Evelyn, Madison, Bobby, Danielle

-- 07 Get the names of suspects who made a call of less than 1 minute on the day of the crime
SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60;
-- Roger, Evelyn, Ernest, Evelyn, Madison, Russell, Kimberly, Bobby, Victoria

-- 08 Finally, we take the intersection of all cases (04,05,06,07) to get the name of the thief
-- Result: The thief is Ernest

-- 09 Get the departure destination
SELECT city FROM airports
WHERE id = ( SELECT destination_airport_id FROM flights
             WHERE day = 29 AND month = 7 AND year = 2020
             ORDER BY hour, minute LIMIT 1);
-- The thief ESCAPED TO: London

-- 010 Get the Accomplice
SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.receiver
    WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"
    AND caller = (SELECT phone_number FROM people WHERE name = "Ernest");
-- 011 The ACCOMPLICE is: Berthold