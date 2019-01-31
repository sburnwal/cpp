#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void testStringStream();

void testStringStream() {
	stringstream ss;
	cout << "current string stream is " << ss.str().c_str() << " net size " << strlen(ss.str().c_str()) << endl;

	ss << "satish";
	ss << "karan";

	cout << "Existing vector size after adding " << ss.str().c_str() << " net size " << strlen(ss.str().c_str()) << endl;
}
