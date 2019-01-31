#include <iostream>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/algorithm/string.hpp>

void teststr(std::string k) {
	printf("size %lu\n", k.length());
	printf("got input %s\n", k.c_str());
}

const std::string teststrr(int i) {
	std::string hh;
	if(i % 2 == 0) {
		char hello[3] = {'a', 'b', '\0'};
		hh.append(hello);
	}

	return hh;
}

void testStringPointer() {
	printf("------ testStringPointer() ----------\n");
	std::string* test = new std::string("satish");
	printf("name is %s\n", test->c_str());
	printf("name is %s\n", (*test).c_str());
}

void testBoostSharedPtrString() {
	printf("------ testBoostSharedPtrString() ----------\n");
	boost::shared_ptr<std::string> test(new std::string("satish"));
	printf("boost name is %s\n", test.get()->c_str());
	printf("boost name is %s\n", test->c_str());
}

void testBoostTrim() {
	printf("------ testBoosTrim() ----------\n");
	char* test = NULL;
	printf("hhell1\n");
	std::string teststr(test);
	printf("hhell2\n");
	boost::algorithm::trim(teststr);
	printf("hhell3\n");
	printf("trimmed string is %s\n", teststr.c_str());
}

int main() {
	char he[5];
	he[4] = 0;

	printf("char array %s, length %lu\n", he, strlen(he));
	std::string xy = std::string(he);
	printf("string is %s\n", xy.c_str());

	teststr(std::string(he));

	char lHostName[128];
	lHostName[127] = 0;
	printf("char array %s, length %lu size is = %lu\n", lHostName, strlen(lHostName), sizeof(lHostName));

	if (gethostname(lHostName, 127) == 0
		&& 0 != strncmp("none", lHostName, 128)
		&& 0 != strncmp("(none)", lHostName, 128)
		&& 0 != strncmp("localhost", lHostName, 128))
	{
		std::cout << "hostname is " << std::string(lHostName) << "\n";
		printf("hostname is %s\n", lHostName);
		printf("hostname is %s\n", boost::asio::ip::host_name().c_str());

	}

	std::string ss = teststrr(2);
	if(!ss.empty()) std::cout << "teststrr is " << ss << "\n";

	testStringPointer();

	testBoostSharedPtrString();

	testBoostTrim();

	return 0;
}
