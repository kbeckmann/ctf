CC=gcc
CFLAGS+=-g -Wall -Wextra -ansi
LDFLAGS+=-z execstack
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=ctf

all: $(EXECUTABLE) cppcheck

cppcheck:
	if [ -x "`which cppcheck`" ]; then cppcheck $(SOURCES); fi 
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

