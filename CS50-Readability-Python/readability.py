from cs50 import get_string
import string

#get text from the user
text = get_string("Your text: ")

#split text into a list
mylist = text.split()

#count number of words
num_words = len(mylist)

#count number of letters
num_letters = 0
for letter in text:
    if letter in string.ascii_letters:
            num_letters = num_letters + 1

#count number of sentences
periods = text.count(".")
questionmarks = text.count("?")
exclamation = text.count("!")
num_sentences = periods + questionmarks + exclamation

#Coleman-Liau index with L as the average number of letters per 100 words and S as the average number of sentences per 100 words in the text
L = 100.0 * num_letters / num_words
S = 100.0 * num_sentences / num_words
index = round((0.0588 * L) - (0.296 * S) - 15.8)

#print resulting index
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(index))












