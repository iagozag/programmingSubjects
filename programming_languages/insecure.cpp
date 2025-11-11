#include <iostream>

int main(){
	int x = 42;
	float* ptr = (float*)&x;

	std::cout << x << std::endl;
	*ptr = 42.5;
	std::cout << x << std::endl;
}
