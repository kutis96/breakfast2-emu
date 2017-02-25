# Declaration of variables
CC = gcc
CC_FLAGS = -w -Wall -std=c99
 
# File names
EXEC = run
SOURCES = $(wildcard src/*.c) $(wildcard src/*/*.c) 
OBJECTS = $(SOURCES:.c=.o)
INCDIRS = src \
          src/bf2emu \
	  src/common

INC_PARAMS=$(foreach d, $(INCDIRS), -I$d)

# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.c
	$(CC) $(INC_PARAMS) -c $(CC_FLAGS) $< -o $@


# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)