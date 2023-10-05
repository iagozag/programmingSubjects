#include <stdio.h>
#include <stdlib.h>

int actual_calc(int a, int b){
  int c;
  c=a/b;
  return c;
}

int calc(){
  int a;
  int b;
  a=14;
  b=2;
  return actual_calc(a, b);;
}

int main(){
  calc();
  return 0;
}

