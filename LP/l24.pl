gcd(N, 0, N) :- !.
gcd(A, B, G) :-
	R is A mod B,
	gcd(B, R, G).
