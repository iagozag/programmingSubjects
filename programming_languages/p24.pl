is_triple(A, B, C) :-
	between(1, 10, A),
	between(1, 10, B),
	between(1, 10, C),
	A2 is A*A,
	B2 is B*B,
	C2 is C*C,
	C2 is A2+B2.
