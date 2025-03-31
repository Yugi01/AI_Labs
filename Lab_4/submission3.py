import re
from collections import defaultdict
from itertools import islice
import math

#The prior in this case is just 1/ the number of plays since they are all unique.
# if it was similar to the spam it would be the number of emails classified as ham or spam. 
# but in this case they are unique so its just 1 over the number of plays since they are all equally likely.

#The probabilty is equal to the number of times a word appears in the document.
#divided by the total number of words in the document.

# The words we want to predict which book it comes from.
input = input()
words_search = re.sub(r'[^A-Za-z\s]', '', input).lower().split()

#used to make a dict with values default values as integers starting at 0.
plays = ["ado.txt","hamlet.txt","lear.txt","macbeth.txt","merchant.txt","midsummer.txt","othello.txt","romeo.txt","tempest.txt","twelfth.txt"]
prior = 1/10 #since there is 10 plays each equally as likely.
probabilty=dict.fromkeys(plays,0)
#making the prob a dict to check which one has the highest prob.

christian_name ={
"merchant.txt":"The Merchant of Venice",
"romeo.txt":"Romeo and Juliet",
"tempest.txt":"The Tempest",
"twelfth.txt":"Twelfth Night",
"othello.txt":"Othello",
"lear.txt":"King Lear",
"ado.txt":"Much Ado About Nothing",
"midsummer.txt":"Midsummer Night’s Dream",
"macbeth.txt":"Macbeth",
"hamlet.txt":"Hamlet",
}

for play in plays:
    # print(play)
    prob = 0
    # print(play)
    with open(f'{play}', 'r') as file:
        raw_content = file.read()
        content = re.sub(r'[^A-Za-z\s]', '', raw_content).lower()
        words = content.split()

    number_of_entries=defaultdict(int)
    for word in words:
        number_of_entries[word] +=1

    total_count = sum(number_of_entries.values())
    prob = 1
    for query_word in words_search:
        prob *= number_of_entries[query_word]/total_count
    # print(math.log(prob)) if prob !=0 else print(0)

    probabilty[play] = prob* prior

print(christian_name[max(probabilty, key=probabilty.get)])