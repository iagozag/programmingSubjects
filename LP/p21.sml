fun ins (x, nil) = [x]
  | ins (x, (h::t)) = if x < h then (x :: h :: t) else h :: (ins (x, t));

fun inSortR nil = nil
  | inSortR (h::t) = ins(h, inSortR t);

fun inSortF x = foldl (fn (a, b) => ins(a, b)) [] x;
