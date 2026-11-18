different(X, Y) :- X \= Y.

coloring(A, B, C, D, E) :-
    member(A, [красный, зелёный, синий]),
    member(B, [красный, зелёный, синий]),
    member(C, [красный, зелёный, синий]),
    member(D, [красный, зелёный, синий]),
    member(E, [красный, зелёный, синий]),
    % 7 конкретных ограничений смежности:
    different(A, B),   % A–B
    different(A, C),   % A–C
    different(B, C),   % B–C
    different(B, D),   % B–D
    different(C, D),   % C–D
    different(C, E),   % C–E
    different(D, E).   % D–E
