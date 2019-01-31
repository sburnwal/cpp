/*
 * HeaderTest.h
 *
 *  Created on: Apr 3, 2018
 *      Author: sburnwal
 */
#include <string>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

namespace demo
{
	class Address
	{
		private:
			std::string addressLine;

		public:
			Address(const std::string& p);
			std::string getAddressLine();
	};

	class Person
	{
		private:
			int age;
			std::string name;
			Address address;

		public:
			static int MAX_AGE;
			Person(const std::string& name, const Address& adr);
			bool setAge(int p);
			int getAge() const;
	};
}
