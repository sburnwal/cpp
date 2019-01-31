#include "myclass.h"
#include <string>
#include <iostream>

const int& MyClass::foo() const {
    //return MyClass::fooPrivate("satish");
	int k = 10;
	return k;
}

int MyClass::fooPrivate(const std::string& ac) {
    return ac.length();
}

int main() {
	std::cout << "Testing...\n";
	MyClass x;
	std::cout << "value " << x.foo() << " \n";
}
