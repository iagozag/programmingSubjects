fun il3rl x = map real x;

fun ordList x = map ord x;

fun squareList x = map(fn a => a*a) x;

fun multPairs x = map(fn (a, b) => a*b) x;

fun incList x y = map(fn a => a+y) x;

fun sqSum x = foldl (op +) 0 (map (fn a => a*a) x);

fun bor x = foldl (fn (a, b) => a orelse b) false x;

fun band x = foldl (fn (a, b) => a andalso b) true x;

fun bxor x = foldl (fn (a, b) => if a then not b else b) false x;

fun dupList x = foldr (fn (a, b) => a :: a :: b) nil x;

fun mylength x = foldl (op +) 0 (map (fn a => 1) x);

fun is2absrl x = map (fn a => if a < 0 then (real (~a)) else (real a)) x;

fun trueCount x = foldl (op +) 0 (map (fn a => if a then 1 else 0) x);

fun maxPairs x = map(fn (a, b) => if a > b then a else b) x;

fun myImplode x = foldr (fn (a, b) => (str a) ^ b) "" x;

fun lconcat x = foldr (fn (a, b) => a @ b) nil x;

fun max [] = raise Empty
  | max (x::xs) = foldl (fn (a, b) => if a > b then a else b) x xs;

fun min [] = raise Empty
  | min (x::xs) = foldl (fn (a, b) => if a < b then a else b) x xs;

fun member (e, l) = bor (map(fn a => if a = e then true else false) l);

fun append x y = foldr (fn (a, b) => a :: b) y x;

fun less (e, l) = foldr(fn (a, b) => if a < e then a :: b else b) nil l;

fun evens x = foldr(fn (a, b) => if a mod 2 = 0 then a :: b else b) nil x;

fun convert x = foldr(fn ((a, b), (c, d)) => (a :: c, b :: d)) (nil, nil) x;

fun myMap f x = foldr (fn (a, b) => f a :: b) nil x;

fun eval (l, x) = foldr (fn (a, b) => a+x*b) 0.0 l;
