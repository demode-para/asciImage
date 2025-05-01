all: stb_image.h main.o
	gcc ./build/main.o -I. -lm -o asciImage

main.o: main.c
	mkdir build
	gcc -c main.c -I. -o ./build/main.o
