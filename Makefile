# CC = g++
CFLAGS  = -std=c++14 -g -Wall -DWORK_AROUND_STRDUP

# The build target 
TARGET = main

OUT = ToyRobot
CC = g++
ODIR = obj
SDIR = source
INC = -Iinc

_OBJS = main.o game.o robot.o table.o command.o command_parser.o util.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

.PHONY: clean

clean:
	rm $(ODIR)/*.o $(OUT)
	