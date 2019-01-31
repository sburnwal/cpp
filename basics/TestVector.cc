/*
 * TestVector.cc
 *
 *  Created on: Mar 16, 2018
 *      Author: sburnwal
 */


#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testVector() {
	vector<string> names;
	cout << "Existing vector size " << names.size() << endl;

	names.push_back("satish");
	names.push_back("karan");
	cout << "Existing vector size after adding " << names.size() << endl;
}
