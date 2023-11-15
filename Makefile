SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
INC_DIR=include

PROG_NAME=main
CFLAGS=-I$(INC_DIR) -g

SRCS=main.cpp
OBJS:=$(SRCS:.c=.o)
OBJS:=$(addprefix $(OBJ_DIR)/,$(OBJS))

all: check_dirs $(BIN_DIR)/mshell 

$(BIN_DIR)/main: $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	cc $(CFLAGS) -c $< -o $@

check_dirs:
	test -d $(OBJ_DIR) || mkdir $(OBJ_DIR)
	test -d $(BIN_DIR) || mkdir $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(OBJS) 
