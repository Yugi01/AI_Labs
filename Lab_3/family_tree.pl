male(greg).
male(adam).
male(trent).
male(martin).
male(marcus).
male(gabriel).
male(dave).
male(michael).
female(lucy).
female(amy).
female(kgomotso).
female(naledi).
female(karen).
female(michelle).
parent(trent,greg).
parent(naledi,greg).
parent(trent,adam).
parent(trent,kgomotso).
parent(karen,adam).
parent(karen,kgomotso).
parent(gabriel,marcus).
parent(gabriel,michelle).
parent(gabriel,naledi).
parent(amy,marcus).
parent(amy,michelle).
parent(amy,naledi).
parent(dave,trent).
parent(dave,martin).
parent(lucy,trent).
parent(lucy,martin).
parent(martin,michael).
married(amy,gabriel).
married(lucy,dave).
married(naledi,trent).

spouse(X,Y) :- married(X,Y).
spouse(X,Y) :- married(Y,X).

mother(X,Y) :- female(X), parent(X,Y).
father(X,Y) :- male(X), parent(X,Y).

siblings(X,Y) :- father(F,X),father(F,Y),mother(M,X),mother(M,Y), X\=Y.

brother(X,Y) :- siblings(X,Y),male(Y).

sister(X,Y) :- siblings(X,Y),female(Y).

half_siblings(X,Y) :- father(P,X),father(P,Y),mother(M1,X),mother(M2,Y),M1\=M2.
half_siblings(X,Y) :- father(F1,X),father(F2,Y),mother(P,X),mother(P,Y),F1\=F2.

half_brother(X,Y) :- male(Y),half_siblings(X,Y).
half_sister(X,Y) :- female(Y),half_siblings(X,Y).

uncle(X,Y) :- father(P,Y),brother(P,X).
aunt(X,Y) :- mother(P,Y),sister(P,X).

grandparent(X,Y) :- parent(P,Y),parent(X,P).
grandmother(X,Y) :- parent(P,Y),mother(X,P).
grandfather(X,Y) :- parent(P,Y),father(X,P).

nephew(X,Y) :- parent(P,X),siblings(P,Y),male(X).
niece(X,Y) :- parent(P,X),siblings(P,Y),female(X).

cousin(X,Y) :- parent(P1,X),parent(P2,Y),siblings(P1,P2).

in_law(X,Y) :- spouse(P,X),(siblings(P,Y);parent(Y,P)).
brother_in_law(X,Y) :- spouse(P,X),brother(P,Y).
sister_in_law(X,Y) :- spouse(P,X),sister(P,Y).