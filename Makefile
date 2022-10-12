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

$(OUTPUT_OBJ_DIR)/test_main.o : $(TEST_SOURCE_DIR)/test_main.cpp $(GTEST_HEADERS)
	$(CC) $(GTEST_CPPFLAGS) -c $(TEST_SOURCE_DIR)/test_main.cpp -o $(OUTPUT_OBJ_DIR)/test_main.o

$(TEST) : $(OUTPUT_OBJ_DIR)/test_main.o $(OUTPUT_OBJ_DIR)/gtest_main.a
	$(CC) $(GTEST_CPPFLAGS) -lpthread $^ -o $@

.PHONY: clean

clean:
	rm $(OUTPUT_OBJ_DIR)/*.o $(OUT)
