OBJECTS = ConstructionTest.o DerivedTest.o
TARGETS = ConstructionTest DerivedTest

all: $(OBJECTS) $(TARGETS)

.PHONY = clean

clean:
	rm ConstructionTest.o ConstructionTest DerivedTest DerivedTest.o

$(OBJECTS): %.o : %.cc
	g++ -g -c -std=c++0x -Wall $(INCLUDES) $< -o $@
	
$(TARGETS): % : %.o
	g++ -g -o $@ $<
