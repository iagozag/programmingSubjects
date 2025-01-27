invert([], []).
invert([X], [X]).
invert([X,Y|T], [Y,X|T2]) :- invert(T, T2).
