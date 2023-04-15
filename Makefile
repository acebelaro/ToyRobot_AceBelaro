# ---------------------------------------------------------------------
#                            Directories
# ---------------------------------------------------------------------

SOURCE_DIR		= source
INCLUDE_DIR		= include
TEST_SOURCE_DIR	= ./test
GTEST_DIR		= ./googletest/googletest
OUTPUT_OBJ_DIR	= obj
APP_SOURCE 		= app/ToyRobotApp.cpp

# ---------------------------------------------------------------------
#                            CPP flags
# ---------------------------------------------------------------------

BUILD_CPPFLAGS	= -std=c++14
BUILD_CPPFLAGS	+= -g
BUILD_CPPFLAGS	+= -Wall
BUILD_CPPFLAGS	+= -DWORK_AROUND_STRDUP
BUILD_CPPFLAGS	+= -I$(INCLUDE_DIR)
	
GTEST_CPPFLAGS	= -std=c++14
GTEST_CPPFLAGS	+= -g
GTEST_CPPFLAGS	+= -Wall
GTEST_CPPFLAGS	+= -Wextra
GTEST_CPPFLAGS	+= -pthread
GTEST_CPPFLAGS	+= -isystem $(GTEST_DIR)/include
GTEST_CPPFLAGS	+= -I$(INCLUDE_DIR)

# ---------------------------------------------------------------------
#                            Other variables
# ---------------------------------------------------------------------

# Compiler
CC 				= g++

# All Google Test headers
GTEST_HEADERS 	= $(GTEST_DIR)/include/gtest/*.h \
                	$(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ 	= $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# The build target 
ifeq ($(OS),Windows_NT)
OUT 			= ToyRobot
TEST 			= test_ToyRobot
else
OUT 			= ToyRobot.out
TEST 			= test_ToyRobot.out
endif

TARGET = ToyRobotApp

SOURCES := .\source\command_parser.cpp \
		   .\source\command.cpp \
		   .\source\robot.cpp \
		   .\source\table.cpp \
		   .\source\util.cpp \

${TARGET}: ${SOURCES}
	${CC} ${BUILD_CPPFLAGS} -o ${TARGET} ${SOURCES} ${APP_SOURCE}

tests: $(TEST)

$(OUTPUT_OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CC) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc -o $(OUTPUT_OBJ_DIR)/gtest-all.o 

$(OUTPUT_OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CC) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc -o $(OUTPUT_OBJ_DIR)/gtest_main.o

$(OUTPUT_OBJ_DIR)/gtest.a : $(OUTPUT_OBJ_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(OUTPUT_OBJ_DIR)/gtest_main.a : $(OUTPUT_OBJ_DIR)/gtest-all.o $(OUTPUT_OBJ_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(OUTPUT_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp 
	$(CC) -c -o $@ $< $(BUILD_CPPFLAGS) 

$(OUTPUT_OBJ_DIR)/%.o: $(TEST_SOURCE_DIR)/%.cpp 
	$(CC) $(GTEST_CPPFLAGS) -c -o $@ $< -DWORK_AROUND_STRDUP

SRC_OBJ = $(OUTPUT_OBJ_DIR)/util.o $(OUTPUT_OBJ_DIR)/table.o $(OUTPUT_OBJ_DIR)/command.o \
	$(OUTPUT_OBJ_DIR)/robot.o $(OUTPUT_OBJ_DIR)/command_parser.o

_TEST_OBJS = test_util.o test_table.o test_robot.o test_command_parser.o
TEST_OBJS = $(patsubst %,$(OUTPUT_OBJ_DIR)/%,$(_TEST_OBJS))

$(TEST) : $(TEST_OBJS) $(SRC_OBJ) $(OUTPUT_OBJ_DIR)/gtest_main.a
	$(CC) $(GTEST_CPPFLAGS) -lpthread $^ -o $@

.PHONY: clean

clean:
	rm $(OUTPUT_OBJ_DIR)/*.o $(OUTPUT_OBJ_DIR)/*.a $(OUT) $(TEST)
