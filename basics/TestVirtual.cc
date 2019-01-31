#include <iostream>
#include "Human.h"

int main() {
	hr::Human* h = hr::Human::getHuman(20, "John", "PLAYER");
	std::cout << "Role is " << h->getRole() << std::endl;
}
