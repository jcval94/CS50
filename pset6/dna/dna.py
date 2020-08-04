from sys import argv, exit


# Best practices
if (len(argv) != 3):
    print("Missing command-line argument")
    exit(1)

# Open CSV
df = open(argv[1])
dfr = df.read()

# First row
Rows = dfr.partition('\n')
first_row = Rows[0]
fr_split = first_row.split(',')

# STRs list
STRs = fr_split[1:(len(fr_split) + 1)]

# Open sequence
sq = open(argv[2])
sqr = sq.read()

# print(sqr)

# storage

Conteos = []


for STR in STRs:
    matches = []
    primera_vez = False
    # letra_count = 0
    for letra in range(len(sqr) - len(STR)):
        # letra_count += 1
        contador = 0
        # print(str(letra_count) + " " + str(len(sqr)))
        for letra_str in range(len(STR)):
            if(sqr[letra_str + letra] == STR[letra_str]):
                contador += 1
        # Print
        # if (STR == 'TATC' and letra_count < 675):
        #     print(sqr[letra_str] + " " + STR[letra_str] + " " + str(contador))

        if (contador == len(STR)):
            matches.append(1)
            if(primera_vez):
                if(matches[letra - len(STR)] != 0):
                    matches[letra] = matches[letra - len(STR)] + 1
            primera_vez = True
        else:
            matches.append(0)
    Conteos.append(max(matches))

# Comparar

ca = 0

for row in dfr.split("\n"):
    ca += 1
    if (ca == 1):
        continue
    repeticiones = row.split(',')[1:(len(row) + 1)]
    repeticiones = [int(i) for i in repeticiones]

    if(repeticiones == Conteos):
        print(row.split(',')[0])
        exit(0)

print("No match")
exit(1)
