from cs50 import get_string


while True:

    s = get_string("Text: ")

    if (len(s) > 0):
        break

# Here, L is the average number of letters per 100 words in the text,
# S is the average number of sentences per 100 words in the text.

let = 0
word = 1
oracion = 0
for i in range(len(s)):
    # Word count
    if (s[i] == " " and s[i + 1] != " "):
        word += 1
    if (s[i] in [".", "!", "?"]):
        oracion += 1
    if (s[i].isupper() or s[i].islower()):
        let += 1

# average per 100 words
L = let / word * 100
S = oracion / word * 100

# print(let)
# print(word)

index = int(round(0.0588 * L - 0.296 * S - 15.8, 0))

if (index < 1):
    print("Before Grade 1")
elif (index > 15):
    print("Grade 16+")
else:
    print("Grade ", index)
