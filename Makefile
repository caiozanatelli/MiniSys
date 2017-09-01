M2_TARGET = ./M2
S2_TARGET = ./S2
 
LIBS = -lm
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
 
CLEAN = rm src/M2/*.o src/S2/*.o
 
.PHONY: default all clean
 
default: $(M2_TARGET) $(S2_TARGET)
all: default
 
M2_OBJECTS = $(patsubst src/M2/%.c, src/M2/%.o, $(wildcard src/M2/*c))
M2_HEADERS = $(wildcard src/M2/*.h)
 
S2_OBJECTS = $(patsubst src/S2/%.c, src/S2/%.o, $(wildcard src/S2/*c))
S2_HEADERS = $(wildcard src/S2/*.h)
 
src/M2/%.o: %.c $(M2_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
   
src/S2/%.o: %.c $(S2_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
     
.PRECIOUS: $(M2_TARGET) $(M2_OBJECTS) $(S2_TARGET) $(S2_OBJECTS)
 
$(M2_TARGET): $(M2_OBJECTS)
	$(CC) $(M2_OBJECTS) -o $@
     
$(S2_TARGET): $(S2_OBJECTS)
	$(CC) $(S2_OBJECTS) -o $@
     
clean:
	$(CLEAN)
