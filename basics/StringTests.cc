#include <string>
#include <iostream>

void testCharPointerContat();

void testCharPointerContat() {
	char* s1 = "Hello Satish";
	char* s2 = " Burnwal";

	std::string s11(s1);
	std::string s21(s2);

	std::string s3 = s11 + s21;
	std::cout << "Result is " << s3 << " length "<< (s11 + s21).length() << std::endl;
}
