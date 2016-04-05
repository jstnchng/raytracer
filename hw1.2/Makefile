CC  = gcc
CXX = clang++

INCLUDES = -I/usr/local/include/OpenEXR -I/usr/include/OpenEXR -I./headerfiles

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) 

LDFLAGS = -g

LDLIBS  = -lIlmImf -lImath -lHalf 

objects = camera.o main.o parser.o point.o ray.o surface.o sphere.o vector.o plane.o material.o intersection.o light.o rgb.o

prog.out: $(objects)
	$(CXX) $(objects) $(LDLIBS) -o prog.out

$(objects): ./headerfiles/camera.h ./headerfiles/main.h ./headerfiles/parser.h ./headerfiles/point.h ./headerfiles/ray.h ./headerfiles/sphere.h ./headerfiles/surface.h ./headerfiles/vector.h ./headerfiles/plane.h ./headerfiles/material.h ./headerfiles/intersection.h ./headerfiles/light.h ./headerfiles/rgb.h

.PHONY: clean
clean:
	rm -f *~ a.out core *.o main *.dSYM prog.out

.PHONY: all
all: clean main

.PHONY: ts1
ts1: prog.out
	./prog.out testscene1.txt hw1.2.exr

.PHONY: ts2
ts2: prog.out
	./prog.out testscene2.txt hw1.2.exr

.PHONY: ts3
ts3: prog.out
	./prog.out testscene3.txt hw1.2.exr

.PHONY: ts4
ts4: prog.out
	./prog.out testscene4.txt hw1.2.exr

.PHONY: ts5
ts5: prog.out
	./prog.out testscene5.txt hw1.2.exr

