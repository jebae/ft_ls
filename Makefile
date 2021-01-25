NAME = ft_ls

# path
SRC_DIR = ./srcs
INC_DIR = ./includes
OBJ_DIR = ./objs
LIB_DIR = ./libs

LIBFT = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf

INCLUDES = -I $(INC_DIR)\
		   -I $(LIBFT)/includes\
		   -I $(FT_PRINTF)/includes\

LIBS = -L $(LIBFT) -lft\
	   -L $(FT_PRINTF) -lftprintf\

# srcs
SRCS = list.c\
	   sort.c\
	   print.c\
	   parse_flags.c\
	   compare.c\

TESTS = *.test.cpp

# commands
deps:
	make -C $(LIBFT) all
	make -C $(FT_PRINTF) all

def = ''

test: deps $(addprefix $(SRC_DIR)/, $(SRCS)) $(SRC_DIR)/$(TESTS)
	g++\
		-Wall -Wextra -std=c++11\
		$(def)\
		-lgtest\
		$(LIBS)\
		$(INCLUDES)\
		$(addprefix $(SRC_DIR)/, $(SRCS)) $(SRC_DIR)/$(TESTS)\
		-o test

.PHONY: test deps
