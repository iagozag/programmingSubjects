datatype 'a option = NONE | SOME of 'a

fun smldiv (n: real, d: real) : real option =
    if Real.==(d, 0.0) then NONE
    else SOME (n / d)
