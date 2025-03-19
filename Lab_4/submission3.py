import re
from collections import defaultdict
from itertools import islice

#used to make a dict with values default values as integers starting at 0.
number_of_entries=defaultdict(int)
play = input()

with open(f'{play}', 'r') as file:
    raw_content = file.read()
    content = re.sub(r'[^A-Za-z\s]', '', raw_content).lower()
    words = content.split()

for word in words:
    number_of_entries[word] +=1

#sort the dictionary based on the second value, i.e. the number of times the word appears.
sorted_words = dict(sorted(number_of_entries.items(), key=lambda item: item[1],reverse=True))

#islice used to remove the first 3 words from out sorted list sorted_words
top_3_words = dict(islice(sorted_words.items(), 3))
for key in top_3_words:
    print(key)