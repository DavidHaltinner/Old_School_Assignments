split([],[],[]).
split([H|T], [H|Pos], Neg) :-
    H >= 0, 
    !,
    split(T,Pos,Neg).
split([H|T], Pos, [H|Neg]) :-
    H < 0,
    split(T,Pos,Neg).

