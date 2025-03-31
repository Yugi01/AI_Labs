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
log_probabilty=dict.fromkeys(plays,0)
final_probs = dict.fromkeys(plays,0)
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

final_final_fr_prob = dict.fromkeys(christian_name.values(),0)

for play in plays:
    prob = 1
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
    #-100 because when the prob is logged is becomes a neg number so -100 essentially makes it 0%
    log_probabilty[play] = math.log(prob)*prior if prob!=0 else -100
    probabilty[play] = prob* prior

A = log_probabilty[max(log_probabilty, key=log_probabilty.get)]
# print(A)
total_log = 0
for play in plays:
    total_log += math.exp(log_probabilty[play]-A)
# final_probs = A+math.log(math.exp(log_probabilty - A) + )
# print("TOTAL",total_log)
final_log = A + math.log(total_log)
for play in plays:
    final_probs[play] = log_probabilty[play] - final_log
# print(log_probabilty)
for play in plays:
    final_final_fr_prob[play] = math.exp(final_probs[play])*100
# print(christian_name[max(probabilty, key=probabilty.get)])
# print(sum(final_final_fr_prob.values())) # total 100 nice.
for play in plays:
    print(f'{christian_name[play]} : {final_final_fr_prob[play]:.2f}%')
    
