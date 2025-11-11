resolution([HeadClause|TailClause], [HeadGoal|TailGoal], NewGoals) :-
    unify_with_occurs_check(HeadClause, HeadGoal),
    append(TailClause, TailGoal, NewGoals).

sumList([], 0).
sumList([H|T], S) :- sumList(T, Rest), S is H+Rest.

distance(L, N, D) :- sumList(L, X), D is abs(X-N).

comb(0, _, []).
comb(N, [H|T], [H|T1]) :- N > 0, N1 is N-1, comb(N1, T, T1).
comb(N, [_|T], C) :- N > 0, comb(N, T, C).

allCombs(L, M, ListResults) :- findall(C, comb(M, L, C), ListResults).

min(A, B, A) :- A =< B.
min(A, B, B) :- B < A.

findClosest([X], _, X).
findClosest([H|T], N, X) :- distance(H, N, D), findClosest(T, N, X1), distance(X1, N, D1), (D < D1 -> X = H; X = X1).

cumulo(L, M, N, Result, Distance) :-
	allCombs(L, M, ListCombinations),
	findClosest(ListCombinations, N, Result),
	distance(Result, N, Distance).
