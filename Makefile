# ---------------------------------------------------------------------
#                            Directories
# ---------------------------------------------------------------------

SOURCE_DIR		= source
TEST_SOURCE_DIR	= ./test
GTEST_DIR		= ./googletest/googletest
OUTPUT_OBJ_DIR	= obj

# ---------------------------------------------------------------------
#                            CPP flags
# ---------------------------------------------------------------------

BUILD_CPPFLAGS	= -std=c++14
BUILD_CPPFLAGS	+= -g
BUILD_CPPFLAGS	+= -Wall
BUILD_CPPFLAGS	+= -DWORK_AROUND_STRDUP
	
GTEST_CPPFLAGS	= -std=c++14
GTEST_CPPFLAGS	+= -g
GTEST_CPPFLAGS	+= -Wall
GTEST_CPPFLAGS	+= -Wextra
GTEST_CPPFLAGS	+= -pthread
GTEST_CPPFLAGS	+= -isystem $(GTEST_DIR)/include
GTEST_CPPFLAGS	+= -I$(SOURCE_DIR)

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
OUT 			= ToyRobot
TEST 			= test_ToyRobot

_OBJS = main.o game.o robot.o table.o command.o command_parser.o util.o
OBJS = $(patsubst %,$(OUTPUT_OBJ_DIR)/%,$(_OBJS))

$(OUTPUT_OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp 
	$(CC) -c -o $@ $< $(BUILD_CPPFLAGS) 

$(OUT): $(OBJS)
	$(CC) $(BUILD_CPPFLAGS) -o $(OUT) $(OBJS)

tests: $(TEST)

$(OUTPUT_OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CC) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc -o $(OUTPUT_OBJ_DIR)/gtest-all.o 

$(OUTPUT_OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CC) $(GTEST_CPPFLAGS) -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest_main.cc -o $(OUTPUT_OBJ_DIR)/gtest_main.o

$(OUTPUT_OBJ_DIR)/gtest.a : $(OUTPUT_OBJ_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(OUTPUT_OBJ_DIR)/gtest_main.a : $(OUTPUT_OBJ_DIR)/gtest-all.o $(OUTPUT_OBJ_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(OUTPUT_OBJ_DIR)/test_util.o : $(TEST_SOURCE_DIR)/test_util.cpp $(GTEST_HEADERS)
	$(CC) $(GTEST_CPPFLAGS) -c $(TEST_SOURCE_DIR)/test_util.cpp -o $(OUTPUT_OBJ_DIR)/test_util.o

$(OUTPUT_OBJ_DIR)/test_table.o : $(TEST_SOURCE_DIR)/test_table.cpp $(GTEST_HEADERS)
	$(CC) $(GTEST_CPPFLAGS) -c $(TEST_SOURCE_DIR)/test_table.cpp -o $(OUTPUT_OBJ_DIR)/test_table.o

$(OUTPUT_OBJ_DIR)/test_robot.o : $(TEST_SOURCE_DIR)/test_robot.cpp $(GTEST_HEADERS)
	$(CC) $(GTEST_CPPFLAGS) -c $(TEST_SOURCE_DIR)/test_robot.cpp -o $(OUTPUT_OBJ_DIR)/test_robot.o

$(OUTPUT_OBJ_DIR)/test_command_parser.o : $(TEST_SOURCE_DIR)/test_command_parser.cpp $(GTEST_HEADERS)
	$(CC) $(GTEST_CPPFLAGS) -c $(TEST_SOURCE_DIR)/test_command_parser.cpp -o $(OUTPUT_OBJ_DIR)/test_command_parser.o

TEST_OBJ = $(OUTPUT_OBJ_DIR)/test_util.o $(OUTPUT_OBJ_DIR)/test_table.o $(OUTPUT_OBJ_DIR)/test_robot.o $(OUTPUT_OBJ_DIR)/test_command_parser.o
SRC_OBJ = $(OUTPUT_OBJ_DIR)/util.o $(OUTPUT_OBJ_DIR)/table.o $(OUTPUT_OBJ_DIR)/command.o $(OUTPUT_OBJ_DIR)/robot.o $(OUTPUT_OBJ_DIR)/command_parser.o

$(TEST) : $(TEST_OBJ) $(SRC_OBJ) $(OUTPUT_OBJ_DIR)/gtest_main.a
	$(CC) $(GTEST_CPPFLAGS) -lpthread $^ -o $@

.PHONY: clean

clean:
	rm $(OUTPUT_OBJ_DIR)/*.o $(OUT)
