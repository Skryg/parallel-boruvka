SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
INC_DIR=include
TEST_DIR=tests

PROG_NAME=main
CC=g++
CFLAGS=-I$(INC_DIR) -g -std=c++17 -pthread -fopenmp -fsanitize=address

SRCS=main.cpp dsu.cpp seq_boruvka.cpp par_boruvka_openmp.cpp par_boruvka_threads.cpp
OBJS:=$(SRCS:.cpp=.o)
OBJS:=$(addprefix $(OBJ_DIR)/,$(OBJS))

TEST_SRCS=test.cpp graph_generator.cpp program_options.cpp dsu.cpp
TEST_OBJS:=$(TEST_SRCS:.cpp=.o)
TEST_OBJS:=$(addprefix $(OBJ_DIR)/,$(TEST_OBJS))

all: check_dirs $(BIN_DIR)/$(PROG_NAME)

$(BIN_DIR)/$(PROG_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

check_dirs:
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)
	test -d $(TEST_DIR) || mkdir $(TEST_DIR)
	test -d $(TEST_DIR)/bin || mkdir $(TEST_DIR)/bin

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(OBJS)
	rm -f -r $(TEST_DIR)/bin
	
tests: check_dirs $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_DIR)/bin/test $(TEST_OBJS)
	touch $(TEST_DIR)/gentests.sh
	touch $(TEST_DIR)/removetests.sh
	
