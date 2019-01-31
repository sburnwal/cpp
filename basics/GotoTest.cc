#include <iostream>

int testme() {
	int i = 10;

	if(i == 11) {
		i = i - 3;
		goto label1;
	}

	label1:
	return i - 2 ;
}

int main() {
	int k = testme();
	std::cout << " i is " << k << std::endl;
	return 0;
}
