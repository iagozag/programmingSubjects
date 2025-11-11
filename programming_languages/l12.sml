datatype suit = HEARTS
			  | CLUBS
			  | DIAMONDS
			  | SPADES;

fun suitname s = 
	case s of HEARTS => "Hearts"
	    	| CLUBS => "Clubs"
	    	| DIAMONDS => "Diamonds"
	    	| SPADES => "Spades";

datatype number = INT of int | REAL of real;

fun plus (x, y) =
  case (x, y) of (INT a, INT b) => INT (a + b)
    		   | (INT a, REAL b) => REAL (real a + b)
    		   | (REAL a, INT b) => REAL (a + real b)
    		   | (REAL a, REAL b) => REAL (a + b);

datatype intnest = INT of int | LIST of intnest list;

fun addUp (INT x) = x
  | addUp (LIST []) = 0
  | addUp (LIST (h::t)) = addUp h + addUp (LIST t);

datatype 'element mylist = NIL | CONS of 'element * 'element mylist;

fun prod NIL = 1
  | prod (CONS (h, t)) = h * prod(t);

fun reverse x = 
	let fun rev NIL aux = aux
		  | rev (CONS(h, t)) aux = rev t (CONS(h, aux))
	in rev x NIL
	end;

fun append NIL b = b
  | append (CONS(h, t)) b = CONS(h, append t b);

datatype 'data tree = Empty | Node of 'data tree * 'data * 'data tree

fun revTree Empty = Empty
  | revTree (Node(l, x, r)) = Node(revTree r, x, revTree l);

fun appendall Empty = []
  | appendall (Node(l, x, r)) = appendall l @ x @ appendall r;

fun isComplete Empty = true
  | isComplete (Node(l, x, r)) = 
	let
		fun aux Empty = (0, true)
	    | aux (Node(l, _, r)) =
			let
				val (qntl, okl) = aux l
				val (qntr, okr) = aux r
			in
				if okl andalso okr andalso qntl+qntr <> 1 then (1, true)
				else (0, false)
			end
		val (a, b) = aux (Node(l, x, r))
	in
		b
	end;

fun makeBST [] = Empty
  | makeBST (h::t) =
	let
		val prev = makeBST t;
		fun aux Empty x = Node(Empty, x, Empty)
		  | aux (Node(l, v, r)) x = if x < v then Node(aux l x, v, r) else if x > v then Node(l, v, aux r x) else Node(l, v, r) 
	in
		aux prev h
	end;

fun searchBST Empty _ = false
  | searchBST (Node(l, v, r)) x = if x < v then searchBST l x else if x > v then searchBST r x else true;

datatype exp = NUM of int |
			   SUM of exp * exp |
			   MUL of exp * exp |
			   UNMINUS of exp

fun interpret (NUM x) = x
  | interpret (UNMINUS x) = ~(interpret x)
  | interpret (MUL (x, y)) = (interpret x) * (interpret y)
  | interpret (SUM (x, y)) = (interpret x) + (interpret y);
