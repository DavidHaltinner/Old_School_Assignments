female(jane).
female(judy).
female(jackie).
male(don).
male(david).
male(danny).
male(fred).
male(frank).
parent(judy, frank).
parent(jackie, fred).
parent(don, david).
parent(danny, don).
parent(don,judy).
parent(don,jackie).
parent(jane, judy).
parent(jane, jackie).

mother(X,Y) :- female(X), parent(X,Y).

father(X,Y) :- male(X), parent(X,Y).

sister(X,Y) :- female(X), female(Y), parent(A,X), parent(A,Y), not(X=Y). 

grandson(X,Y) :- male(X), parent(A,X), parent(Y,A).

firstCousin(X,Y) :- parent(A, X), parent(B, Y), parent(C, A), parent(C, B), not(X=Y).

descendent(X,Y) :- parent(Y,X).
descendent(X,Y) :- parent(Y,Z), descendent(X, Z).

