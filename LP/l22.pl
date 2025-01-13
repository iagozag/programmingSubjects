sum(List, X) :- sum(List, 0, X).

sum([], X, X).
sum([H|T], C, X) :- NC is C+H, sum(T, NC, X).

myappend([], L, L).
myappend([H|T], L, [H|LAux]) :- myappend(T, L, LAux).

myreverse(L, R) :- myreverse(L, R, []).
myreverse([], R, R).
myreverse([H|T], R, L) :- myappend([H], L, X), myreverse(T, R, X).

subsetsum(V, X, S) :- subsetsum(V, X, 0, [], S).

subsetsum([], X, X, S, S).
subsetsum([H|T], X, Y, R, S) :- NY is Y+H, subsetsum(T, X, NY, [H|R], S).
subsetsum([_|T], X, Y, S, R) :- subsetsum(T, X, Y, S, R).

riddle([], _).
riddle(_, []).

enigma(L1, N, L2) :- length(L1, S), S >= N, R is S-N, enigma_take(R, L1, L2).

enigma_take(0, _, []) :- !.
enigma_take(N, [H|T], [H|L2]) :- N > 0, N1 is N-1, enigma_take(N1, T, L2).

factorial(N, F) :- factorial(N, 1, F).
factorial(1, F, F).
factorial(N, C, F) :- integer(N), N > 1, N1 is N-1, NC is C*N, factorial(N1, NC, F).
