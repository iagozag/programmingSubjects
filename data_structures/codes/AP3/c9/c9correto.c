#include <stdlib.h>

int* f(void) {
int* x = malloc(10 * sizeof(int));
x[9] = 0; 
return x;
}

int main(void) {

int* a = f();
free(a);
return 0;
}
