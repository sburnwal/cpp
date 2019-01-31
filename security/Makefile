OBJECTS = TestKeyPair.o TestKeyPair2.o TestKeyPair3.o SSLContextTest.o
TARGETS = TestKeyPair TestKeyPair2 TestKeyPair3 SSLContextTest
EXTRA_LIBS = -lssl -lcrypto 

all: $(TARGETS) 

.PHONY = all
.PHONY = clean

$(OBJECTS): %.o : %.cc
	g++ -g -c -std=c++11 -Wall -I/usr/local/Cellar/openssl/1.0.2o_1/include $< -o $@
	
$(TARGETS): % : %.o
	g++ -g -o $@ $(EXTRA_LIBS) $<

clean:
	rm $(OBJECTS) $(TARGETS)