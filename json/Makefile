INCLUDES = -I/usr/local/Cellar/openssl/1.0.2o_1/include \
			-I../myincludes \
			-I../../rapidjson/include
			
OBJECTS = jsontest.o RapidJsonTest.o base64.o
TARGETS = jsontest RapidJsonTest

all: $(OBJECTS) $(TARGETS)  

.PHONY = all
.PHONY = clean

$(OBJECTS): %.o : %.cc
	g++ -g -c -std=c++0x -Wall $(INCLUDES) $< -o $@
	
$(TARGETS): % : %.o
	g++ -g -o $@ -lssl -lcrypto $<

clean:
	rm $(OBJECTS) $(TARGETS)
