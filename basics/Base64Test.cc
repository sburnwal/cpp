#include <iostream>
#include <unistd.h>

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = ( char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = ( char_array_4[0] << 2       ) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) +   char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = 0; j < i; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

int testc(const char *in, char* out) {
	std::cout << in << "\n";
	std::cout << "222\n";
	*(out) = 'h';
	*(out+1) = 'e';
	*(out+2) = 'l';
	*(out+3) = 'l';
	std::cout << "333\n";
	return 2;
}

int main() {
	const std::string s = "satish burnwal";
	std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
	std::string decoded = base64_decode(encoded);

	std::cout << "encoded: " << encoded << std::endl;
	std::cout << "decoded: " << decoded << std::endl;

	uint8_t* name = (uint8_t*) s.c_str();
	unsigned char* name2 = (unsigned char*) s.c_str();

	std::cout << "encoded: " << name << std::endl;
	std::cout << "decoded: " << name2 << std::endl;

	const char* a = "karanjjje";
	char b[5];
	//std::unique_ptr<char[]> b(new char[6]);
	std::cout << "111\n";
	testc(a, b);
	//b[4] = '\0';
	std::cout << "444\n";
	std::cout << b << std::endl;
	std::cout << "555\n";

	std::string header = "eyJ0eXAiOiJqd3QiLCJhbGciOiJSUzI1NiJ9";
	std::string payload = "eyJkb21haW5zIjpbeyJuYW1lIjoiRE9NQUlOX0VBUEdHSEVERyIsInJvbGVzUiI6MTgxNzMzODc3ODkzNDczNTYyNDUsInJvbGVzVyI6MTU2NjM3MTcxMDgwNjMyMjc4MjV9LHsibmFtZSI6IkRPTUFJTl9DQU5GSEtOSE4iLCJyb2xlc1IiOjEwMDM0NDUxODgxMTg1MTE5MTU0LCJyb2xlc1ciOjU2MjMxMDExNjI0OTA4MjE5NTF9LHsibmFtZSI6IkRPTUFJTl9QTk5IQUVJSUwiLCJyb2xlc1IiOjYxNTU1NTcyMDIwMjc3ODcwNzQsInJvbGVzVyI6MTcwMDMwNDA4MDk0ODUzMTAyOTJ9LHsibmFtZSI6IkRPTUFJTl9LT0hJSUtHSEEiLCJyb2xlc1IiOjcxNzA0MjM2MDA0OTI4NDk5NjIsInJvbGVzVyI6MTUwNjE4NjQzNDk4NTg3MTEyNzF9LHsibmFtZSI6IkRPTUFJTl9FRUpQRUpCSE8iLCJyb2xlc1IiOjEyNDU4Mjk4NDE4NzMwNDA4NTYxLCJyb2xlc1ciOjExOTk5MzU2MDQ5NzQxMDI2NTI2fV0sImlzcyI6Im15aXNzc3VlciIsInN1YiI6Imluc2llbWUtYWRtaW4iLCJhdWQiOiJBUElDLUFwcHMiLCJpYXQiOjYxMTMyMzksImV4cCI6NjExNjgzOX0";
	std::string data = header + '.' + payload;
	printf("header: %s\n", header.c_str());
	printf("payload: %s\n", payload.c_str());
	printf("data: %s\n", data.c_str());

	const char* kdata = "AgAAAAAAAAAAAAAAAAAAADyQsXNh1XTmqKW7apHiBsMqxxuxgy7YI3hOWJ0K0mrNvpYhtBZdrRooKIUBJuzwLgVER4xDObNdjOgQx3Y/68Ce65D/sNbxcwLvAdOwKGpzf3dxpGtDl2LHcLZW/fXwQgLK8L0z90WAB6MaFEV/J1zSh7ZIoPgQn1A0dApgdWTUcJrtH/UVTksF+zE+z12JbA==";
	std::string lData(kdata);
	const char PERIOD = '.';
	printf("data is : %s\n", lData.c_str());

	uint32_t lPos = lData.find(PERIOD, 0);
	printf("position %u\n", lPos);
	if(lPos != std::string::npos) {
		printf("data has period \n");
	} else {
		printf("data has no period \n");
	}
	return 0;
}

