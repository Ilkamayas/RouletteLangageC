# Makefile pour le projet Roulette

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I. $(shell sdl2-config --cflags)
# La macro -Dmain=SDL_main sera appliquée uniquement pour main.c
CFLAGS_MAIN = -Dmain=SDL_main
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRCS = main.c audio.c game_logic.c sdl_utils.c graphics.c
OBJS = main.o audio.o game_logic.o sdl_utils.o graphics.o
TARGET = roulette_game

all: $(TARGET)

# Compilation de main.c avec la macro -Dmain=SDL_main
main.o: main.c
	$(CC) $(CFLAGS) $(CFLAGS_MAIN) -c main.c -o main.o

# Compilation des autres fichiers sans -Dmain=SDL_main
audio.o: audio.c
	$(CC) $(CFLAGS) -c audio.c -o audio.o

game_logic.o: game_logic.c
	$(CC) $(CFLAGS) -c game_logic.c -o game_logic.o

sdl_utils.o: sdl_utils.c
	$(CC) $(CFLAGS) -c sdl_utils.c -o sdl_utils.o

graphics.o: graphics.c
	$(CC) $(CFLAGS) -c graphics.c -o graphics.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)
