#include <iostream>
#include "Human.h"

namespace hr {
	std::string Player::getRole() {
		return role;
	}

	Human* Player::getHuman(int a, std::string s, std::string r) {
		return new Player(a, s, r);
	}
}
