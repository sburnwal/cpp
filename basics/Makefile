INCLUDES = -I/usr/local/Cellar/openssl/1.0.2o_1/include \
			-I/usr/local/include \
			-I. \
			-I../../rapidjson/include
			
OBJECTS = RegexTest.o RegexTest2.o TimeTest.o Base64.o Base64Test.o ClassMembers.o CharTest.o GotoTest.o StringTest.o \
		  BoostTest.o PointerTest.o Human.o Player.o Engineer.o TestVirtual.o IOStreamTest.o

TARGETS = RegexTest TimeTest Base64Test ClassMembers CharTest GotoTest StringTest BoostTest PointerTest \
		   IOStreamTest RegexTest2

EXTRA_LIBS = -lboost_system
DEPENDENCIES = Base64.o 

all: $(OBJECTS) $(TARGETS) 

.PHONY = all
.PHONY = clean

$(OBJECTS): %.o : %.cc
	g++ -g -c -std=c++0x -Wall $(INCLUDES) $< -o $@
	
$(TARGETS): % : %.o
	g++ -g $(EXTRA_LIBS) -o $@ $< $(DEPENDENCIES)  

clean:
	rm $(OBJECTS) $(TARGETS)	 
