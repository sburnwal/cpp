#include <boost/shared_ptr.hpp>
#include <iostream>

void testBoostSharedPtr() {
	char* s = NULL;
	boost::shared_ptr<char> s_ptr(s);
	if(s_ptr.get() == NULL) {
		printf("shared ptr has null object\n");
	} else {
		printf("shared ptr has non-null object\n");
	}
}

int main() {
	testBoostSharedPtr();
	return 0;
}
