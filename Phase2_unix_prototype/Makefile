CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LFLAGS =
LIBS = -lm
SOURCES = commands.cc PhaseII.cc utilities.cc
OBJECTS = $(subst .c,.o,$(SOURCES))
EXE = Phase2.exe
.PHONY: clean help

Phase2.exe : commands.o PhaseII.o utilities.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

%.o : %.cc
	$(CC) $(CFLAGS) -c $<

all : $(EXE)

clean:
	rm -f $(OBJECTS) $(EXE) *~

help:
	@echo "Valid targets:"
	@echo "  clean:  removes .o and .exe files"
