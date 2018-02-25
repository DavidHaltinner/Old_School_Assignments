comb([X|L],M) :- comb(L,M).
comb([X|L],[X|M]) :- comb(L,M).
comb([],[]).

sumlist([],0).
sumlist([X|Rest],Sum) :- sumlist(Rest, Sum1), Sum is X + Sum1.

subsetsum(L, Sum, SubL) :- comb(L, SubL), sumlist(SubL, Total), Total=Sum.

