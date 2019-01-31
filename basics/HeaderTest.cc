#include "../../cpp/basics/HeaderTest.h"

namespace demo
{
	//using constructor initialization
	Address::Address(const std::string& adrLine): addressLine(adrLine)
	{

	}

	std::string Address::getAddressLine()
	{
		return addressLine;
	}

	int Person::MAX_AGE = 200;
	Person::Person(const std::string& pname, const Address& padr ) :  name(pname), address(padr)
	{
		std::cout << "Person(3) created " << std::endl;
	}

	bool Person::setAge(int p)
	{
		if(p > Person::MAX_AGE) {
			std::cout << "Age limit exceeded\n";
			return false;
		}
		age = p;
		std::cout << "Age updated" << std::endl;
		return true;
	}

	int Person::getAge()
	{
		return age;
	}
}

