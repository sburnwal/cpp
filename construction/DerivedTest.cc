#include <iostream>

class A {
private:
	int i;
	int k;

public:
	A(int p) : A(p, 0) {
		std::cout << "Constructor A(int) called\n";
	}

	A(int p, int q) : i(p), k(q) {
		std::cout << "Constructor A(int, int) called\n";
	}

	virtual ~A() {
		std::cout << "Destructior ~A() called()\n";
	}

	virtual int getValue() {
		std::cout << "A.getValue()\n";
		return i+k;
	}
};

class B : public A {
private:
	int n;

public:
	B(int p, int q) : A(p, q), n(0) {
		std::cout << "Constructor B(int, int) called\n";
	}

	virtual ~B() {
		std::cout << "Destructior ~B() called()\n";
	}

	virtual int getValue();
};

int B::getValue() {
	std::cout << "B.getValue()\n";
	return n;
}

int main() {
	A* a = new B(10, 20);
	std::cout << "getValue(): " << a->getValue() << std::endl;;

	const int i = 10;

	std::string k;
	std::cout << "k is null ? " << (k == NULL) << std::cout;
	std::cout << "getValue(): " << a->getValue() << std::endl;;
}
