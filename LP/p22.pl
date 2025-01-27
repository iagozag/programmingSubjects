rangelist(N, []) :- N >= 0.
rangelist(N, [_|T]) :- N1 is N-1, rangelist(N1, T).

submulset([], _).
submulset([H|T], L) :- member(H, L), submulset(T, L).

multset(N, L, S) :-
	rangelist(N, S),
	submulset(S, L).
