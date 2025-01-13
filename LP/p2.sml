fun nand (a, b) = if a andalso b then false else true;

fun nandl l = foldl nand true l;

fun nandr l = foldr nand true l;

fun comp l = nandl l = nandr l;

fun fib x =
	let
		fun fibAux 0 = [0]
		  | fibAux 1 = [1,0]
		  | fibAux x =
			let
				val (a::b::t) = fibAux (x-1)
			in
				(a+b)::a::b::t
			end;

		val (h::t) = fibAux x
	in
		h
	end;
