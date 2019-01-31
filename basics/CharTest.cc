#include <iostream>
#include <array>

void testSize(long ar[]) {
	char* k = new char[2]{'k', 'l'};
	printf("k is %s\n", k);
	delete k;

	printf("size in function %lu\n", sizeof(ar) );
	printf("length %lu\n", sizeof(ar) );
	printf("k is %s\n", k);

	std::array<int, 3> nums;
	nums.at(0) = 1;
	nums.at(1) = 2;

	std::cout << nums[0] << std::endl;


}

int main() {
	char test1[5];
	test1[4] = 0;
	printf("test1 array %s, length %lu\n", test1, strlen(test1));

	char test2[128];
	test2[127] = 0;
	printf("test2 array %s, length %lu\n", test2, strlen(test2));

	long days[] = {1,2,3,4,5};
	int temp = 10;
	int md[temp];
	testSize(days);
	long *ptr = days;
	printf("%lu\n", sizeof(days) );
	printf("%lu\n", sizeof(ptr) );
}
