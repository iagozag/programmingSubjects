#include <stdio.h>
#include <stdlib.h>

int foo(int** a, int i, int j) {
	return a[i][j];
}
int bar(int b[2][3], int i, int j) {
	return b[i][j];
}

int main() {
	int** a = (int**)malloc(2 * sizeof(int*));
	a[0] = (int*)malloc(3 * sizeof(int));
	a[1] = (int*)malloc(3 * sizeof(int));
	a[0][0] = 0; a[0][1] = 1; a[0][2] = 2;
	a[1][0] = 3; a[1][1] = 4; a[1][2] = 5;
	int b[2][3] = {{0, 1, 2}, {3, 4, 5}};
	int c[3][2] = {{10, 20}, {30, 40}, {50, 60}};
	printf("E: %d\n", bar(c, 1, 1));
}
