file2list(File, List) :-
    open(File, read, Stream),
    read_lines(Stream, List),
    close(Stream).

read_lines(Stream, []) :-
    at_end_of_stream(Stream),
    !.
read_lines(Stream, [Line|T]) :-
    \+ at_end_of_stream(Stream),
    read(Stream, Line),
    read_lines(Stream, T).

search([], _, []).
search([H|T], A, [H|T1]) :- 
	atom_chars(H, HC),
	sort(HC, X), 
	atom_chars(A, AC),
	sort(AC, X), 
	search(T, A, T1).
search([_|T], A, S) :- search(T, A, S).

findAnagram(DIC, A, S) :-
	file2list(DIC, L),
	search(L, A, S).


partition(_, [], [], []).
partition(H, [H1|T1], [H1|L], R) :-
    H1 =< H, !,
    partition(H, T1, L, R).
partition(H, [H1|T1], L, [H1|R]) :-
    partition(H, T1, L, R).

quickselect([H|T], K, E) :-
    partition(H, T, L, R),
    length(L, N),
    I is N + 1,
    (   K = I -> E = H
    ;   K < I -> quickselect(L, K, E)
    ;   NK is K - I, quickselect(R, NK, E)
    ).

median(L, M) :-
    length(L, N),
    K is (N+1) // 2,
    quickselect(L, K, M).
