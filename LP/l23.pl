max(X, Y, X) :- X >= Y.
max(X, Y, Y) :- Y > X.


maxList([X], X).
maxList([H|T], M) :- maxList(T, X), (H < X -> M = X; M = H).


ordered([]).
ordered([_]).
ordered([X,Y|T]) :- X =< Y, ordered([Y|T]).


divide(L, 0, [], L).
divide([H|T], N, [H|L], R) :-
    N > 0,
    N1 is N - 1,
    divide(T, N1, L, R).

join([], R, R).
join(L, [], L).
join([H|L], [H2|R], [H|X]) :- H < H2, join(L, [H2|R], X).
join([H|L], [H2|R], [H2|X]) :- H >= H2, join([H|L], R, X).

mergesort([],[]).
mergesort([X],[X]).
mergesort(In,Out) :-
	length(In, N),
	N > 1,
	N2 is N//2,
	divide(In, N2, L, R),
	mergesort(L, X), mergesort(R, Y),
	join(X, Y, Out).


up2N(N,N,[N]) :- !.
up2N(H,N,[H|T]) :- H < N, H1 is H+1, up2N(H1, N, T).

nocheck(_, [], _).
nocheck(H, [H1|T], Xd) :-
	H =\= H1,
	X is abs(H-H1),
	X =\= Xd,
	Xd1 is Xd+1,
	nocheck(H, T, Xd1).

queens(_, []).
queens(N, [H|T]) :-
	queens(N, T),
	up2N(1, N, L),
	member(H, L),
	nocheck(H, T, 1).

nqueens(N, S) :-
	length(S, N),
	queens(N, S).


weight([],0).
weight([food(_,W,_) | Rest], X) :-
	weight(Rest,RestW),
	X is W + RestW.

calories([],0).
calories([food(_,_,C) | Rest], X) :-
	calories(Rest,RestC),
	X is C + RestC.

subseq([],[]).
subseq([Item | RestX], [Item | RestY]) :-
	subseq(RestX,RestY).
subseq(X, [_ | RestY]) :-
	subseq(X,RestY).

legalKnapsack(Pantry,Capacity,Knapsack) :-
	subseq(Knapsack, Pantry),
	weight(Knapsack,W),
	W =< Capacity.

addKnap(Pantry, Capacity, Knapsack, NewKnapsack) :-
	member(Item, Pantry),
	legalKnapsack([Item | Knapsack], Capacity, NewKnapsack).

maxC([],Sofar,_,Sofar).
maxC([First | Rest],_,MC,Result) :-
	calories(First,FirstC),
	MC =< FirstC,
	maxC(Rest,First,FirstC,Result).
maxC([First | Rest],Sofar,MC,Result) :-
	calories(First,FirstC),
	MC > FirstC,
	maxC(Rest,Sofar,MC,Result).
maxCalories([First | Rest],Result) :-
	calories(First,FirstC),
	maxC(Rest,First,FirstC,Result).

multiknap(Pantry,Capacity,Knapsack) :-
	findall(K,addKnap(Pantry,Capacity, [], K),L),
	maxCalories(L,Knapsack).


edge(a, b).
edge(a, c).
edge(b, c).
edge(a, d).
edge(b, e).
edge(d, e).
edge(a, e).

subList([], []).
subList([H|T], [H|L]) :- subList(T, L).
subList([_|T], L) :- subList(T, L).

has_edge(_, []).
has_edge(U, [H|T]) :-
	edge(U, H), has_edge(U, T).
has_edge(U, [H|T]) :-
	edge(H, U), has_edge(U, T).

clique([]).
clique([H|T]) :- has_edge(H, T), clique(T).

cliqueN(N, G, L) :- subList(G, L), length(L, N), clique(L).
