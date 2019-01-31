#include <regex>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include "Base64.h"

int main() {
	const uint8_t magic[5] = { 0x8a, 0x7b, 0x22, 0x7a, 0x67 };
	const static uint32_t INSIEME_MAGIC_LEN = 5;

	std::string input =
			"The cat cat bites the dog dog.\nThis not desirable.\nThey both live together.";
	std::cout << "Input is: " << input << std::endl;

	std::regex newline("\n");
	std::string nl = "\\n";

	std::string output = std::regex_replace(input, newline, nl);
	std::cout << "Output is : " << output << std::endl;

	std::string test = "{\"typ\":\"jwt\",\"alg\":\"";
	test += "RS256";
	test += "\"}";
	std::cout << "header is : " << test << std::endl;

	uint32_t count = 0;
	for (int i = 0; i < 10; i++) {
		count++;
	}
	std::cout << "count is : " << count << std::endl;

	count = 0;
	std::string testStr = "satish burnwalhgi";
	std::cout << " strlen(): " << strlen(testStr.c_str()) << " length(): "
			<< testStr.length() << std::endl;
	uint8_t* testStrData = new uint8_t[1024];
	for (int i = 0; i < testStr.length(); i++) {
		testStrData[count++] = testStr[i];
	}
	std::cout << " size to encode " << count << std::endl;

	webtoken::Base64 encoded(testStrData, count);
	const uint8_t* encodedData = encoded.getData();
	std::cout << "encodedData " << encodedData << " length "
			<< strlen((char*) encodedData) << std::endl;

	uint8_t* decodedData;
	uint32_t outLength;
	encoded.decode(&decodedData, outLength);
	std::cout << "decoded is: " << decodedData << " length: " << outLength
			<< " org-length: " << encoded.getLength() << " actual: "
			<< strlen((char*) decodedData) << " " << ((char*) decodedData)
			<< std::endl;
	for (int n = 0; n < outLength; n++) {
		if (decodedData[n] == '\0') {
			std::cout << "null char at index " << n << std::endl;
		} else {
			std::cout << "char at index " << n << " is " << decodedData[n]
					<< std::endl;
		}
	}

	uint8_t* ddata;
	uint32_t dlen;
	webtoken::Base64* b64 = webtoken::Base64::factory(encodedData,
			strlen((char*) encodedData));
	b64->decode(&ddata, dlen);
	std::cout << "decoded data " << ddata << " length " << dlen << " getLength "
			<< b64->getLength() << std::endl;
	return 0;
}

