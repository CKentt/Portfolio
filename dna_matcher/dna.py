import sys
import csv

if len(sys.argv) != 3:
    print("Missing Command-Line Argument")

with open(sys.argv[2], "r") as file:
    str_string = file.read()
    with open(sys.argv[1], "r") as file1:
        csv_string = csv.reader(file1)
        strs = {}
        first_row = next(csv_string)
        for item in first_row:
            if item == first_row[0]:
                pass
            else:
                strs[item] = 0
        aux = 0
        aux3 = 0
        for item in strs:
            for char in range(len(list(str_string))):
                if str_string[char : char + len(list(item))] == item:
                    aux += 1
                    aux3 = char + len(list(item))
                    while str_string[aux3 : aux3 + len(list(item))] == item:
                        aux += 1
                        aux3 = aux3 + len(list(item))
                    if strs[item] < aux:
                        strs[item] = aux
                    aux = 0
                    aux3 = 0

        aux_2 = False
        for sample in csv_string:
            for i in range(len(sample)):
                if i == 0:
                    pass
                else:
                    if sample[i] == str(strs[first_row[i]]):
                        aux_2 = True
                    else:
                        aux_2 = False
                        break
            if aux_2 == True:
                print(sample[0])
                break
        if aux_2 == False:
            print("No Match")
