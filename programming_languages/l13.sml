fun f () =
  let
    val x = 10
    fun g () = x + 1
  in
    g
  end;

val h = f ();
val result = h ();

fun concat x = foldr (op ^) "" x;
