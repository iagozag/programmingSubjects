fun mymap(nil, f) = nil
  | mymap(h::t, f) = (f h) :: mymap(t, f);

fun square a = a*a;

fun myfoldl(f, x, nil) = x
  | myfoldl(f, x, h::t) = f (h, myfoldl(f, x, t));

fun myfoldr(f, x, nil) = x
  | myfoldr(f, x, h::t) = f (myfoldr(f, x, t), h);
