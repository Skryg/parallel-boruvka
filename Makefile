SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
INC_DIR=include

PROG_NAME=main
CC=g++
CFLAGS=-I$(INC_DIR) -g -O3

SRCS=main.cpp graph_generator.cpp program_options.cpp
OBJS:=$(SRCS:.cpp=.o)
OBJS:=$(addprefix $(OBJ_DIR)/,$(OBJS))

all: check_dirs $(BIN_DIR)/$(PROG_NAME) 

$(BIN_DIR)/$(PROG_NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

check_dirs:
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(OBJS) 
