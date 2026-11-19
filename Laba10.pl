different(X, Y) :- X \= Y.

coloring(A, B, C, D, E) :-
    member(A, [красный, зелёный, синий]),
    member(B, [красный, зелёный, синий]),
    member(C, [красный, зелёный, синий]),
    member(D, [красный, зелёный, синий]),
    member(E, [красный, зелёный, синий]),
    different(A, B),
    different(A, C),
    different(B, C),
    different(B, D),
    different(C, D),
    different(C, E),
    different(D, E).
