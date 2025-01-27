append([], L, L).
append([H|T], L2, [H|R]) :- append(T, L2, R).

mystery1([]).
mystery1([_]).
mystery1([H|T]) :- append(Mid, [H], T), mystery1(Mid).

mystery2([], []).
mystery2([H|T], FlatList) :-
	mystery2(H, FlatH),
	mystery2(T, FlatT),
	append(FlatH, FlatT, FlatList).
mystery2([H|T], [H|FlatT]) :- \+ is_list(H), mystery2(T, FlatT).
