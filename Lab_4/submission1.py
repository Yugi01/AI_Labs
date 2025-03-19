import re

input = input()
sentence = re.sub(r'[^A-Za-z\s]', '', input).lower()

print(sentence)