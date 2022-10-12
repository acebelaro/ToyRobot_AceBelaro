CC = g++
CFLAGS  = -std=c++14 -g -Wall -DWORK_AROUND_STRDUP

# The build target 
TARGET = main

all: $(TARGET)

$(TARGET): main.o game.o robot.o table.o command.o command_parser.o util.o
	$(CC) $(CFLAGS) -o ToyRobot main.o game.o robot.o table.o command.o command_parser.o util.o
	
main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
game.o : game.cpp
	$(CC) $(CFLAGS) -c game.cpp
	
robot.o : robot.cpp
	$(CC) $(CFLAGS) -c robot.cpp
	
table.o : table.cpp
	$(CC) $(CFLAGS) -c table.cpp
	
command.o : command.cpp
	$(CC) $(CFLAGS) -c command.cpp
	
command_parser.o : command_parser.cpp
	$(CC) $(CFLAGS) -c command_parser.cpp
	
util.o : util.cpp
	$(CC) $(CFLAGS) -c util.cpp

clean:
	$(RM) $(TARGET)