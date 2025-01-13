parent(kim,holly).
parent(kent,rob).
parent(margaret,kim).
parent(margaret,kent).
parent(esther,margaret).
parent(herbert,margaret).
parent(herbert,jean).
greatgrandparent(GGP,GGC) :- 
  parent(GGP,GP), parent(GP,P), parent(P,GGC).

female(kim).
female(margaret).
female(esther).
female(kent).
female(jean).
female(holly).
male(herbert).

mother(X, Y) :- parent(X, Y), female(X).

father(X, Y) :- parent(X, Y), male(X).

sister(X, Y) :- parent(Z, X), parent(Z, Y), female(X), female(Y), X \= Y.

grandson(X, Y) :- parent(X, Z), parent(Z, Y).

firstCousin(X, Y) :- parent(A, X), parent(B, Y), parent(P, A), parent(P, B).

descendant(X, Y) :- parent(Y, X).

third([_,_,Y|_], Y).

firstPair([X,X|_]).

del3([X,Y,_|T],[X,Y|T]).

dupList([],[]).
dupList([H|T], [H,H|Z]) :- dupList(T,Z).

isDuped([]).
isDuped([H,H|T]) :- isDuped(T).

oddSize([_]).
oddSize([_,_|T]) :- oddSize(T).

prefix([], _).
prefix([H|T], [H|Z]) :- prefix(T, Z).

isMember(X, [X|_]).
isMember(X, [_|T]) :- isMember(X,T).

isUnion([],[],_).
isUnion([H|T], [A|B], Z) :- isMember(H, Z), isMember(A, Z), isUnion(T, B, Z).
