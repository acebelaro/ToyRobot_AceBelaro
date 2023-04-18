# ---------------------------------------------------------------------
#                            Directories
# ---------------------------------------------------------------------

SOURCE_DIR		= source
INCLUDE_DIR		= include
TEST_SOURCE_DIR	= ./test

# ---------------------------------------------------------------------
#                            CPP flags
# ---------------------------------------------------------------------

BUILD_CPPFLAGS	= -std=c++14
BUILD_CPPFLAGS	+= -g
BUILD_CPPFLAGS	+= -Wall
BUILD_CPPFLAGS	+= -I$(INCLUDE_DIR)

# ---------------------------------------------------------------------
#                            Other variables
# ---------------------------------------------------------------------

# Compiler
CC			= g++

# The build target 
TARGET 		= ToyRobot
TEST		= ToyRobotTest

APP_SOURCE	= .\app\ToyRobotApp.cpp
SOURCES := .\source\direction.cpp \
			.\source\coordinate.cpp \
			.\source\command_parser.cpp \
			.\source\table.cpp \
			.\source\RobotPosition.cpp \
			.\source\robot.cpp

${TARGET}: ${SOURCES}
	${CC} ${BUILD_CPPFLAGS} -o ${TARGET} ${SOURCES} ${APP_SOURCE}

TEST_APP_SOURCE	= .\test\test_toyRobot.cpp
TEST_SOURCES := .\test\test_command_parser.cpp \
				.\test\test_robot.cpp \
				.\test\test_table.cpp \
				.\test\test_direction.cpp

$(TEST): $(TEST_SOURCES)
	${CC} ${BUILD_CPPFLAGS} -I${TEST_SOURCE_DIR} -o ${TEST} ${SOURCES} ${TEST_SOURCES} ${TEST_APP_SOURCE}

test: $(TEST)
	./${TEST}

# Clean command
ifeq ($(OS),Windows_NT)
CLEAN_TARGET	= del ${TARGET}.exe
CLEAN_TEST		= del ${TEST}.exe
else
CLEAN_TARGET	= del ${TARGET}.exe 
CLEAN_TEST		= del ${TEST}.exe 
endif

clean:
	$(CLEAN_TARGET)
	$(CLEAN_TEST)

all: $(TARGET) $(TEST)
	./${TEST}