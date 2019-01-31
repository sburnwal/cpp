#include <iostream>
#include <fstream>
#include <stdio.h>
#include <inttypes.h>

void testCreateEmptyFile();

void testCreateEmptyFile() {
	std::ofstream ofile;
	ofile.open("/Users/sburnwal/Projects/Workspaces/temp/x.txt");
	ofile << "Hello World!";
	ofile.close();

	ofile.open("/Users/sburnwal/Projects/Workspaces/temp/y.txt");
	ofile.close();

	std::cout << "File was created" << std::endl;

	char buffer[200];
	uint64_t i = 100;
	uint64_t j = 200;
	//int p = snprintf ( buffer, 100, "User %s, Domain %s, Read Bits 0x%" PRIx64 ", Write Bits 0x%" PRIx64, "satish", "testdomain", i, j);
	int p = snprintf ( buffer, 100, "User %s, Domain %s, Read Bits 0x%llx, Write Bits 0x%llx", "satish", "testdomain", i, j);
	std::cout << "Final result " << buffer << std::endl;
}

int main() {
	testCreateEmptyFile();
}
