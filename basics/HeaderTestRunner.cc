#include <iostream>

#include "../../cpp/basics/HeaderTest.h"

int main()
{
	std::cout << "Running HeaderTest program" << std::endl;
	demo::Address adr("4205 Lorren Dr");

	demo::Person p("Satish", adr);
	std::cout << "person's age" << p.getAge() << std::endl;
	std::cout << "Updating person's age" << std::endl;
	p.setAge(30);

	const demo::Person p2("karan", adr);
	p2.getAge();

	std::cout << "Completed header test" << std::endl;
}
