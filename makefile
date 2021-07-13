CC=gcc # Compipler to use

INCLUDE_DIR =./include# Header files
SOURCE_DIR =./source# C files


DEBUG_FLAGS= -g -Wall
CFLAGS=-I$(INCLUDE_DIR)

ALL_SOURCES=$(wildcard $(SOURCE_DIR)/*.c)


BBQueue : $(ALL_SOURCES)
	gcc $(DEBUG_FLAGS) -o $@ $^ $(CFLAGS)

clean: # Removes everything
	rm ./BBQueue