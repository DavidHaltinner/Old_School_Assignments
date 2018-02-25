add_at_end(X,List-Tail,List-NewTail):- Tail=[X|NewTail],!.
add_at_end(X,List-[X|NewTail],List-NewTail). 

