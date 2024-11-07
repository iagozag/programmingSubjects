#!/bin/bash
x=1
function g () { echo $x ; x=2 ; }
function f () { local x=3 ; g ; }
f # serah impresso 1 ou 3?
echo $x # serah impresso 1 ou 2?
