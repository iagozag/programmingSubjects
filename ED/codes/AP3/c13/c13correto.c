#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *p;

  p = (char *) malloc(19);
  p = (char *) realloc(p, 12);
  p = (char *) realloc(p, 16);
  free(p);
  return 0;
}


