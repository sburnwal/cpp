#include <iostream>
#include "json.hpp"

int main() {
	nlohmann::json myJson;
	std::string name = "satish";
	const char* lname = "burnwal";
	myJson.emplace("name", "satish");
	myJson["lname"] = lname;
	myJson.emplace("age", 25);
	std::cout << myJson << std::endl;

	nlohmann::json myArray;
	myArray.push_back("tilaiya");
	myArray.push_back("koderma");

	myJson.emplace("cities", myArray);

	std::cout << myJson << std::endl;


	return 0;
}
