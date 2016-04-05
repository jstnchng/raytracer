CC  = gcc
CXX = clang++ -std=c++11

INCLUDES = -I/usr/local/include/OpenEXR -I/usr/include/OpenEXR -I./headerfiles

CFLAGS   = -g -Wall $(INCLUDES)
CXXFLAGS = -g -Wall $(INCLUDES) 

LDFLAGS = -g

LDLIBS  = -lIlmImf -lImath -lHalf 

objects = camera.o main.o parser.o point.o ray.o surface.o sphere.o vector.o plane.o material.o intersection.o light.o rgb.o triangle.o ambientlight.o bbox.o bvhnode.o

hw = hw1.5

$(hw): $(objects)
	$(CXX) $(objects) $(LDLIBS) $(LDFLAGS) -O2 -o prog_out

$(objects): ./headerfiles/camera.h ./headerfiles/main.h ./headerfiles/parser.h ./headerfiles/point.h ./headerfiles/ray.h ./headerfiles/sphere.h ./headerfiles/surface.h ./headerfiles/vector.h ./headerfiles/plane.h ./headerfiles/material.h ./headerfiles/intersection.h ./headerfiles/light.h ./headerfiles/rgb.h ./headerfiles/triangle.h ./headerfiles/ambientlight.h ./headerfiles/bbox.h ./headerfiles/bvhnode.h

.PHONY: clean
clean:
	rm -f *~ a.out core *.o main *.dSYM prog_out $(hw).exr

.PHONY: all
all: clean main

.PHONY: ts1
ts1: $(hw)
	./prog_out ./scenefiles/testscene1.txt hw1.5.exr 3

.PHONY: ts2
ts2: $(hw)
	./prog_out ./scenefiles/testscene2.txt hw1.5.exr 

.PHONY: ts3
ts3: $(hw)
	./prog_out ./scenefiles/testscene3.txt hw1.5.exr 1

.PHONY: ts4
ts4: $(hw)
	./prog_out ./scenefiles/testscene4.txt hw1.5.exr

.PHONY: ts5
ts5: $(hw)
	./prog_out ./scenefiles/testscene5.txt hw1.5.exr

.PHONY: triangle
triangle: $(hw)
	./prog_out ./scenefiles/triangle.txt hw1.5.exr

.PHONY: plane
plane: $(hw)
	./prog_out ./scenefiles/plane.txt hw1.5.exr

.PHONY: teapot
teapot: $(hw)
	./prog_out ./scenefiles/teapot.txt hw1.5.exr 2

.PHONY: rainbow
rainbow: $(hw)
	./prog_out ./scenefiles/rainbow.txt hw1.5.exr 3

.PHONY: kitten
kitten: $(hw)
	./prog_out ./scenefiles/kitten.txt hw1.5.exr 3

.PHONY: fandisk
fandisk: $(hw)
	./prog_out ./scenefiles/fandisk_rescaled.txt hw1.5.exr 1

.PHONY: bunny
bunny: $(hw)
	./prog_out ./scenefiles/bunny.txt hw1.5.exr 3

.PHONY: colored_spheres
colored_spheres: $(hw)
	./prog_out ./scenefiles/colored_spheres.txt hw1.5.exr 0

.PHONY: test
test: $(hw)
	./prog_out ./scenefiles/test.txt hw1.5.exr 1
