fun read_lines file =
    let
        val inStream = TextIO.openIn file
        fun loop () =
            case TextIO.inputLine inStream of
                SOME line => line :: loop ()
              | NONE => []
    in
        loop ()
    end
    handle _ => []

fun parse_t lines =
    map (fn line => map (fn s => valOf (Int.fromString s)) (String.tokens (fn c => c = #" ") line)) lines

fun read_t file = parse_t (read_lines file)

fun max(a, b) = if a < b then b else a;

val memo = Array.tabulate (100, fn _ => Array.array (100, ~1))

fun dp (t: int list list) (i, j) = 
	if i > 99 orelse i < 0 orelse j < 0 orelse j > i then 0
	else if Array.sub(Array.sub(memo, i), j) <> ~1 then Array.sub(Array.sub(memo, i), j)
	else
		let 
			val best = max(dp t (i+1, j), dp t (i+1, j+1))+List.nth (List.nth (t, i), j)
		in
			Array.update(Array.sub(memo, i), j, best);
			best
		end

val t = read_t "in2.txt"

val result = dp t (0, 0)
