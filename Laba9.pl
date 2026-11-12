parent(tom, bob).
parent(tom, liz).
parent(bob, ann).
parent(bob, pat).
parent(liz, kate).
parent(liz, mark).
parent(pat, sara).
parent(mark, dan).

male(tom).
male(bob).
male(mark).
male(dan).

female(liz).
female(ann).
female(pat).
female(kate).
female(sara).

% Базовое правило варианта
% X — дед или бабушка для Z, если существует Y, для которого X — родитель Y, а Y — родитель Z.
grandparent(X, Z) :-
    parent(X, Y),
    parent(Y, Z).

% Собственное производное правило
% X — бабушка для Z, если X — дед/бабушка для Z и X — женщина.
grandmother(X, Z) :-
    grandparent(X, Z),
    female(X).

% https://swish.swi-prolog.org/
