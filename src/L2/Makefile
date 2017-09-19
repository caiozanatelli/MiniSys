TARGET = ./L2
LIBS = -lm
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic -g
CFLAGS = -Wall -std=c99 -g 
CLEAN = rm *o

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, %.o, $(wildcard *c))
HEADERS = $(wildcard *.h)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	 
.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
		   $(CC) $(OBJECTS) -o $@
		   $(CLEAN)
		   		   		 
clean: 
	$(CLEAN)
