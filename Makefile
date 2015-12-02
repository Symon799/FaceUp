## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c99 -O3
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
SRC= pixel_operations.c main.c integral.c haar.c
OBJ= ${SRC:.c=.o}
 
all: main
 
main: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main
 
# END
