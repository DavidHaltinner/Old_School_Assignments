%
% database block.pl -- starting point for the last problem on assignment
%
% member_of and not_member_of define whether or not X is a member
% of a list (the second argument)
%
member_of(X,[X|L]).
member_of(X,[Y|M]) :- member_of(X,M).
%
not_member_of(X,[]).
not_member_of(X,[Y|L]) :-
      different(X,Y),not_member_of(X,L).
%
% Give ourselves some blocks to play with
%
isblock(a).
isblock(b).
isblock(c).
%
% Make sure that Prolog knows the blocks are not identical
%
different(a,b).
different(a,c).
different(b,a).
different(b,c).
different(c,a).
different(c,b).
different(X,table) :- isblock(X).
different(table,Y) :- isblock(Y).
%
% Also define differently configured states
%
different([on(A,X)|State1],[on(A,Y)|State2]) :-
      different(X,Y).
different([on(A,X)|State1],[on(A,X)|State2]) :-
      different(State1,State2).
%
% What does it mean for a block to be clear in a given state?
%
clear(X,[]).
clear(X,[on(B,Y)|State]) :-
      different(X,Y),clear(X,State).
%
% X is on Y in a given State if on(X,Y) is a member of
% the configuration list for the State
%
on(X,Y,State) :- member_of(on(X,Y),State).
%
% update (M,S1,S2) means move M changes state S1 to state S2
%
update(move(X,Y,Z),[on(X,Y)|S],[on(X,Z)|S]).
update(move(X,Y,Z),[on(U,V)|S1], [on(U,V)|S2]) :-
      different(X,U),update(move(X,Y,Z),S1,S2).
%
% Define when a move can be made in a given State
%

% If block B is clear, it can be moved from P1 to the table.

legal_move(move(B,P1,table),State) :-
             on(B,P1,State),
             different(P1,table),
             clear(B,State).

% If block B1 is on P and clear and block B2 is clear, then B1 can be
% moved from P to B2.

legal_move(move(B1,P,B2),State) :-
             isblock(B2),
             on(B1,P,State),
             different(P,B2),
             different(B1,B2),
             clear(B1,State),
             clear(B2,State).
%
% The three-place transform predicate is true if the list of moves
% in Plan leads from State1 to State2
%
transform(State1,State2,Plan) :-
      transform(State1,State2,[State1],Plan).
%
% The four-place transform predicate is true if the list of moves
% leads from State1 to State2 while passing through states in Visited.
% This is needed to avoid returning to a state that we have already
% been in.
%
transform(State,State,Visited,[]).
transform(State1,State2,Visited,[Move|Moves]) :-
             legal_move(Move,State1),
             update(Move,State1,State),
             not_member_of(State,Visited),
             transform(State,State2,[State|Visited],Moves).
%
% The initial table top configuration
%
state1([on(a,b),on(b,table),on(c,a)]).
state2([on(a,b),on(b,c),on(c,table)]).

% state1(S1),state2(S2),transform(S1,S2,P). 

