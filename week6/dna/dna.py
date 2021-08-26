
import csv
import sys


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py FILE.csv FILE.txt")

    # Read datas into memory from file
    results = []    # About each person
    with open(sys.argv[1]) as csvfile:
        read_csv = csv.DictReader(csvfile)
        strs_names = read_csv.fieldnames    # name + qty of STRs
        for row in read_csv:
            results.append(row)

    with open(sys.argv[2]) as dnafile:
        read_dna = dnafile.read()

    strs = []       # About each STRs
    for i in range(1, len(strs_names), 1):      # For each of the STRs
        tmp_qty = 0
        tmp_qty_max = 0
        for letter in range(0, len(read_dna), 1):   # For each letter in a DNA
            j = 0
            if (strs_names[i][j] == read_dna[letter]):
                tmp_qty = 0
                while (strs_names[i][j] == read_dna[letter] and letter < len(read_dna) - 1):
                    j += 1
                    letter += 1
                    if j == len(strs_names[i]):
                        tmp_qty += 1
                        j = 0
                if tmp_qty_max < tmp_qty:
                    tmp_qty_max = tmp_qty
        strs.append(tmp_qty_max)

    lsn = len(strs_names)
    for i in range(0, len(results), 1):        # For each person
        j = 0                               # For each of the STRs
        if int(results[i][strs_names[j + 1]]) == strs[j]:
            while ((int(results[i][strs_names[j + 1]]) == strs[j]) and (j < lsn - 1)):
                if j == lsn - 2:
                    print(results[i]['name'])
                    return
                j += 1
    print("No match")


if __name__ == "__main__":
    main()