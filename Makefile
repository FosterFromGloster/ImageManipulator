CPP=g++
CPPFLAGS=-std=c++11

TARGET = imageops

all: $(TARGET) UnitTests 


unittests.o: catch.hpp unittests.cpp Image.o
	$(CPP) -c -o unittests.o unittests.cpp $(CPPFLAGS)

UnitTests: unittests.o Image.o
	$(CPP) -o UnitTests unittests.o Image.o  $(CPPFLAGS)

$(TARGET): ImageDriver.o Image.o
	$(CPP) ImageDriver.o Image.o -o $(TARGET)  $(CPPFLAGS)  
 
ImageDriver.o: ImageHeader.h Image.o ImageDriver.cpp
	$(CPP) -c -o ImageDriver.o ImageDriver.cpp  $(CPPFLAGS)  

Image.o: Image.cpp ImageHeader.h
	$(CPP) -c -o Image.o Image.cpp  $(CPPFLAGS)  

run_unittest:
	./UnitTests
	
clean:
	@rm *.o imageops UnitTests
run:
	./imageops
