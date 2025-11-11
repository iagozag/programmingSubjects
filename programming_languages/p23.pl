edge(start, a).
edge(start, d).
edge(a, b).
edge(b, c).
edge(a, c).
edge(b, d).
edge(b, e).
edge(d, e).
edge(e, a).
edge(c, end).
edge(e, end).

path(L) :- path(L, []).

path([], _).
path([_], _).
path([U,V|T], Vis) :-
    \+ member(U, Vis),
    edge(U, V),
    path([V|T], [U|Vis]).

last([H], H).
last([_|T], X) :- last(T, X).

cycle([H|T]) :-
	path([H|T]),
	last([H|T], L),
	edge(L, H).

solution([H|T]) :-
	path([H|T]),
	last([H|T], X),
	H = start,
	X = end.

