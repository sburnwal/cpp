#include <iostream>
#include "Human.h"

namespace hr {
	Human* Human::getHuman(int a, std::string s, std::string r) {
		if(r == "PLAYER") {
			return Player::getHuman(a, s, "PLAYER");
		} else {
			return Engineer::getHuman(a, s, "ENGR");
		}
	}
}
