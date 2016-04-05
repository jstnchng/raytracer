CC  = gcc
CXX = clang++

INCLUDES = -I/usr/local/include/OpenEXR -I/usr/include/OpenEXR

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g

LDLIBS = -lIlmImf -lImath -lHalf

hw0:

.PHONY: clean
clean:
	rm -rf  *.o *.out hw0.exr *.cc~ core main hw0 *.dSYM

.PHONY: all
all: clean main

