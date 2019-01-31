#include <iostream>
#include "Human.h"

namespace hr {
	std::string Engineer::getRole() {
		return role;
	}

	Human* Engineer::getHuman(int a, std::string s, std::string r) {
		return new Engineer(25, "Maun", "ENGR");
	}
}
