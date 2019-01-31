#include <iostream>

class A {
private:
	int i;
	int k;

public:
	/*A() {
	 std::cout << "Constructor A() called\n";
	 }*/

	A(int p) : i(p), k(0) {
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
		return i;
	}
};

class B {
private:
	char type;
	A objA;   // B contains A as a member variable

public:
	B(char c = 'X') :
			type(c), objA(5) {
		std::cout << "Constructor B(type=" << type << ") called\n";
	}

	B(char c, int p) :
			type(c), objA(p) {
		std::cout << "Constructor B(type=" << type << ", int) called\n";
	}

	static B updateType(B b, char c) {
		std::cout << "Updating B type=" << b.type << " to " << c << "\n";
		b.type = c;
		return b;
	}

	B(const B& b) :
			type(b.type), objA(b.objA) {
		std::cout << "B() Copy constructor called with type " << b.type << "\n";
	}

	B& operator=(const B& b) {
		std::cout << "B() assignment operator called with type " << b.type
				<< "\n";
		type = b.type;
		objA = b.objA;
		return *this;
	}

	~B() {
		std::cout << "Destructor ~B(type=" << type << ") called\n";
	}

	char getType() {
		return type;
	}

	virtual int getValue();
};

int B::getValue() {
	std::cout << "B.getValue()\n";
	return type;
}

class Person {
private:
	int age;
	std::string name;

public:
	Person(int a, std::string n) {
		age = a;
		name = n;
		std::cout << "Person constructor age=" << age << "\n";
	}

	static Person updateAge(Person p, int a) {
		std::cout << "Updating age from " << p.age << " to " << a << std::endl;
		p.age = a;
		return p;
	}

	Person(const Person& p) :
			age(p.age), name(p.name) {		//copy constructor
		std::cout << "Person Copy constructor\n";
	}

	Person& operator=(const Person& p) {	//assignment operator
		std::cout << "Person assignment operator\n";
		//copy fields
		age = p.age;
		name = p.name;

		//return the existing object
		return *this;
	}

	~Person() {
		std::cout << "Person destructor age " << age << "\n";
	}
};

int main() {
	B b1;
	B b2('Y');
	B b3('N', 20);

	B b4 = b3;
	std::cout << "Object b4 type : " << b4.getType() << std::endl;

	b4 = b1;
	std::cout << "Assignment operator done" << std::endl;

	b4.updateType(b4, 'Z');

	std::cout << "Class of b4 : " << typeid(b4).name() << std::endl;

	Person p1(30, "mukesh");  	//direct initialization
	Person p2(p1);			//copy constructor used
	Person p3 = p1;			//copy constructor used
	Person p4(20, "ramesh");
	p4 = p2;				//assignment operator used

	Person p5 = p4.updateAge(p4, 50);
	std::cout << "Class of p5 : " << typeid(p5).name() << std::endl;

}
