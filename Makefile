## Simple SDL mini code
 
CC=clang
 
CPPFLAGS= `pkg-config --cflags sdl gtk+-2.0`
CFLAGS= -Wall -Wextra -Werror -pedantic -std=c99 -g
LDFLAGS= -lm
LDLIBS= `pkg-config --libs sdl gtk+-2.0` -lSDL_image
 
SRC= pixel_operations.c main.c integral.c haar.c Adaboost.c
OBJ= ${SRC:.c=.o}
 
all: main
 
main: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main
 
# END
