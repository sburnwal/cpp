/*
 * TestRef.cc
 *
 *  Created on: Mar 16, 2018
 *      Author: sburnwal
 */

#include <iostream>

int& getValueByAddress();
int getValueByRef();

void testRef() {
	std::cout << "Hello there!" << std::endl;
	int j = 10;
	int& val = j;

	std::cout << "By Ref " << val << std::endl;		//prints value of val
	std::cout << "By Ref " << &val << std::endl;	//prints address of val
	val = getValueByAddress();
	std::cout << "Function return By Ref " << val << std::endl;
}

int& getValueByAddress() {
	static int i = 10;
	return i;
}

int getValueByRef() {
	int k = 10;
	return k;
}
