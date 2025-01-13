datatype tp = Int of int | Real of real | String of string;

fun sum (x, y) =
	case (x, y) of (Int x, Int y) => Int (x+y)
	    	| (Real x, Real y) => Real (x + y)
	    	| (String x, String y) => String (x^y)
			| _ => raise Fail "Incompatible types";

fun sqSum x = foldl (fn (a, b) => b+a*a) 0 x;

fun dupList x = foldr (fn(a, b) => a::a::b) [] x;
