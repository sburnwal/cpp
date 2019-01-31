#include <iostream>
#include <regex>
#include <string>

void single_slashify(const char* aInUsername, char* aOutUsername) {
	const char* lPtr = (const char*) aInUsername;
	unsigned int lIndex = 0;
	unsigned int lDestIndex = 0;
    while( lIndex < strlen(aInUsername))
    {
        if (lPtr[lIndex] == '\\' && lPtr[lIndex+1] == '\\')
        {
        	std::cout << "slashify again at " << lIndex << std::endl;
        	aOutUsername[lDestIndex] = aInUsername[lIndex];
        	lDestIndex++;
        	lIndex += 2;
        }
        else
        {
        	aOutUsername[lDestIndex] = aInUsername[lIndex];
        	lDestIndex++;
        	lIndex++;
        }
    	std::cout << "at index" << lDestIndex << std::endl;
    }

    std::cout << "at index " << lDestIndex << std::endl;
    aOutUsername[lDestIndex] = 0;
}

int main() {
	std::string name("xdomain\\user2");

	std::regex re("[a-zA-Z0-9][a-zA-Z0-9_.@\\\\-]{0,31}");
	std::smatch m;

	std::regex_search(name, m, re);

	for(auto v: m) std::cout << v << std::endl;

	std::cout << "Testing double slashify..\n";
	std::string aInUsername("apic#Radius\\\\xdomain\\\\satish");
	std::cout << "username is " << aInUsername << std::endl;
	std::string aOutUsername;

	char lBuffer[80];
	const char* lPtr = (const char*) aInUsername.c_str();
	unsigned int lIndex = 0;
    while( lIndex < aInUsername.length())
    {
        if (lPtr[lIndex] == '\\')
        {
        	std::cout << "In double slashify with index = " << lIndex << std::endl;
            if (lPtr[lIndex+1] == '\\')
            {
            	std::cout << "slashify again at " << lIndex << std::endl;
                snprintf(lBuffer, 79, "%c", lPtr[lIndex]);
                aOutUsername += lBuffer;
                lIndex += 2;
                continue;
            }
            else
            {
                snprintf(lBuffer, 79, "%c", lPtr[lIndex]);
                aOutUsername += lBuffer;
                lIndex++;
                continue;
            }
        }
        else
        {
            snprintf(lBuffer, 79, "%c", lPtr[lIndex]);
            aOutUsername += lBuffer;
            lIndex++;
            continue;
        }
    }

    std::cout << "username after double slashify is " << aOutUsername << std::endl;

    lIndex = 0;
    while( lIndex < aOutUsername.length())
    {
    	std::cout << " char is " << aOutUsername.at(lIndex) << std::endl;
    	lIndex++;
    }

    for(unsigned int i = 0; i < aOutUsername.size(); i++) {
    	if(aOutUsername.at(i) == '\\') {
    			std::cout << "char at " << i << " is \\ \n";
    	}
    }

    char* un = "ap\\ic";
    std::cout << "##### username is " << un << std::endl;
    char test[80];
    single_slashify(un, test);
    std::cout << "##### username after is " << test << std::endl;
}
