CC  = gcc
CXX = clang++

INCLUDES = -I/usr/local/include/OpenEXR -I/usr/include/OpenEXR -I./headerfiles

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) 

LDFLAGS = -g

LDLIBS  = -lIlmImf -lImath -lHalf 

objects = camera.o main.o parse.o point.o prp.o ray.o sphere.o vector.o

hw1.1: $(objects)
	$(CXX) $(objects) $(LDLIBS) -o hw1.1 

$(objects): ./headerfiles/camera.h ./headerfiles/main.h ./headerfiles/parse.h ./headerfiles/point.h ./headerfiles/prp.h ./headerfiles/ray.h ./headerfiles/sphere.h ./headerfiles/surface.h ./headerfiles/vector.h 

.PHONY: clean
clean:
	rm -f *~ a.out core *.o main *.dSYM hw1.1

.PHONY: all
all: clean main

.PHONY: ts1
ts1: hw1.1
	./hw1.1 testscene1.txt

.PHONY: ts2
ts2: hw1.1
	./hw1.1 testscene2.txt

.PHONY: ts3
ts3: hw1.1
	./hw1.1 testscene3.txt

.PHONY: ts4
ts4: hw1.1
	./hw1.1 testscene4.txt

.PHONY: ts5
ts5: hw1.1
	./hw1.1 testscene5.txt

