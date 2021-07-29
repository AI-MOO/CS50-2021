import csv
import sys
import re
import numpy as np

# Global Dict: used to store nucleotides reptieion in one sequence (STRs) for text file
STR_dict = {'name': 'someone',
            'AGATC': 0,
            'TTTTTTCT': 0,
            'AATG': 0,
            'TCTAG': 0,
            'GATA': 0,
            'TATC': 0,
            'GAAA': 0,
            'TCTG': 0}

# Global List: fixed nucleotides types
STR_list = ['AGATC', 'TTTTTTCT', 'AATG', 'TCTAG', 'GATA', 'TATC', 'GAAA', 'TCTG']

# List of dictionaries: handling all dna information of people in the database (csv file) e.g:
# [{'name':'Albus','AGATC':15, 'TTTTTTCT':'49', ... }, {'name':'Cedric', 'AGATC':'31', ... }]
List_data = []


def main():
    # must pass three arguments when start the program
    if len(sys.argv) != 3:
        print("Missing Command Line")
        sys.exit(1)

    # check if argv[1] & argv[2] are csv & txt files respectively
    argv_csv = re.search('.csv$', sys.argv[1])
    argv_txt = re.search('.txt$', sys.argv[2])

    # when argv[1] not a csv file return an error
    if (argv_csv == None):
        print("Error: first argument must be a csv file e.g, file.csv")
        sys.exit(1)

    # when argv[2] not a txt file return an error
    elif (argv_txt == None):
        print("Error: second argument must be a text file e.g, file.txt")
        sys.exit(1)

    # counter for number of people in database file
    dictionaries_counter = 0
    # open csv file and store the people and their DNA in List_data
    with open(sys.argv[1], 'r') as csv_file:
        reader = csv.DictReader(csv_file)
        for row in reader:
            dictionaries_counter += 1
            List_data.append(row)

    # open the text file to read the DNA sequence
    with open(sys.argv[2], 'r') as txt_file:
        line = txt_file.read()

    # Run STR repetions and comparsion functions
    STR_outcomes = check_sequential_repetitions(line)
    compare_DNA(STR_outcomes, List_data, dictionaries_counter)


# function: used to obtain the maximum number nucleotides reptieion in one sequence (STRs)


def check_sequential_repetitions(text):

    repetitions = []
    for word in range(len(STR_list)):
        max_reptetions = text.count(STR_list[word])

        if max_reptetions == 0:
            STR_dict[STR_list[word]] = 0

        else:
            for i in range(1, max_reptetions + 1):
                rep = text.count(i * STR_list[word])
                if rep != 0:
                    repetitions.append(rep)
                    STR_dict[STR_list[word]] = str(len(repetitions))

            repetitions.clear()

    return STR_dict

# function: used to compare STR outcomes of text file with all people DNA in database to check the similarites


def compare_DNA(STR_outcomes, List_data, dictionaries_counter):

    arr = []
    for i in range(dictionaries_counter):
        for key in List_data[0]:
            # update 'name' : 'someone' to the name in dataset for comparsion purpose e.g Severus, albus...
            STR_outcomes['name'] = List_data[i]['name']
            compare_e = STR_outcomes[key] == List_data[i][key]
            arr.append(compare_e)

        bool_arr = np.array(arr)
        if np.count_nonzero(bool_arr) == len(List_data[i]):
            print(List_data[i]['name'])
            sys.exit(1)
        else:
            arr.clear()

    print("No match")


if __name__ == "__main__":
    main()