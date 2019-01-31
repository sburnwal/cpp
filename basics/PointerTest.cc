#include <iostream>

class Car {
public:
	Car(int y, std::string m) : year(y), model(m) {
		printf("Car created\n");
	}

	const std::string& getModel() {
		return model;
	}

private:
	int year;
	std::string model;
};

class  Person {
public:
	Person(const Car* c, std::string n) : car(*c), name(n) {
		printf("Person created\n");
	}

	const Car& getCar() {
		return car;
	}

	void updateName() {
		name = "Merc";
	}

	std::string getName() {
		return name;
	}

private:
	Car car;
	std::string name;
};

int testme() {
	int i = 3;
	return i;
}

void gme(int& p) {
	int i = p;
}

int main() {
	const Car* c = new Car(2015, "Toyota Camry");
	Person* p = new Person(c, "some name");
	delete c;

	Car pc = p->getCar();
	std::cout << "Car model " << pc.getModel() << std::endl;

	p->updateName();
	std::cout << "Updated name " << p->getName() << std::endl;

	char* x = "G8CS/PD8SUq8ccd39fzIKw==";
	uint8_t* y = (uint8_t*) "G8CS/PD8SUq8ccd39fzIKw==";

	printf("%s\n", x);
	printf("%s\n", y);

	int k = testme();
	gme(k);
}
