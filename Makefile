CFLAGS = -O3 -Dmain=SDL_main
LDFLAGS = -lm -lmingw32 -lSDL2main -lSDL2
SDL2_INCLUDE_DIR = src/include
SDL2_LIBRARIES_DIR = src/lib

INC = sdl2-light.h library/Display/Display.h library/World/world.h library/Sprites/sprites.h
SRC = main.c sdl2-light.c library/Display/Display.c library/World/world.c library/Sprites/sprites.c

OBJ = $(SRC:%.c=%.o)

PROG = spacecorridor.exe

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $< -I $(SDL2_INCLUDE_DIR) -o $@

$(PROG): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@ -L $(SDL2_LIBRARIES_DIR)

doc: $(PROG)
	doxygen $(PROG)

.PHONY: clean
clean:
	del /f /q *.o *~ $(PROG)
	rd /s /q latex html