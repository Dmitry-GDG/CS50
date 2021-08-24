from cs50 import get_string

inp = get_string("Text: ")
qty_letters = 0
qty_sentences = 0
qty_words = 0
for letter in inp:
    if (((letter >= 'a' and letter <= 'z')) or ((letter >= 'A' and letter <= 'Z'))):
        qty_letters += 1

#   Calculating quantity of words and setences
i = 0
while (i < len(inp)):
    while ((inp[i] >= '\t' and inp[i] <= '\r') or inp[i] == ' '):
        i += 1
    if (inp[i]):
        qty_words += 1
    while (i < len(inp) and inp[i] != '\n' and inp[i] != '\t' and inp[i] != '\v' and inp[i] != '\r' and inp[i] != '\f' and inp[i] != ' ' and inp[i] != '\0' and inp[i] != '.' and inp[i] != '!' and inp[i] != '?'):
        i += 1
    if (i < len(inp) and (inp[i] == '.' or inp[i] == '!' or inp[i] == '?')):
        qty_sentences += 1
        i += 1

#   Calculating grading
outp = round(0.0588 * (qty_letters * 100 / qty_words) - 0.296 * (qty_sentences * 100 / qty_words) - 15.8)
if (outp < 1):
    print("Before Grade 1")
elif (outp > 16):
    print("Grade 16+")
else:
    print("Grade ", outp)

# call it:
# python readability.py
# Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
# Grade 3