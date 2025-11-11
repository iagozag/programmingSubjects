fun myfoldr f x nil = x
  | myfoldr f x (h::t) = f h (myfoldr f x t);

fun myfoldl f x nil = x
  | myfoldl f x (h::t) = f (myfoldl f x t) h;

fun sum nil = 0
  | sum (h::t) = h+sum t;

fun range 0 = nil
  | range 1 = nil
  | range x = x :: range (x-1);


fun inv nil l2 = l2
  | inv (h::t) l2 = inv t (h::l2);
