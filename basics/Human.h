#include <iostream>

namespace hr {
class Human {
private:
	int age;
	std::string name;

public:
	Human(int a, std::string s) : age(a), name(s) {
		std::cout << "Created human age=" << a << "name=" << s << std::endl;
	}

	virtual std::string getRole() = 0;

	static Human* getHuman(int a, std::string s, std::string r);
};

class Player : public Human {
private:
	 std::string role;

public:
	Player(int a, std::string s, std::string r): Human(a, s), role(r) {
		std::cout << "Created player age=" << a << "name=" << s << " role=" << r << std::endl;
	}

	virtual std::string getRole();

	static Human* getHuman(int a, std::string s, std::string r);
};

class Engineer : public Human {
private:
	 std::string role;

public:
	Engineer(int a, std::string s, std::string r): Human(a, s), role(r) {
		std::cout << "Created engineer age=" << a << "name=" << s << " role=" << r << std::endl;
	}

	virtual std::string getRole();

	static Human* getHuman(int a, std::string s, std::string r);
};

}
