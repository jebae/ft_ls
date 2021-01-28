NAME = ft_ls

# path
SRC_DIR = ./srcs
INC_DIR = ./includes
OBJ_DIR = ./objs
LIB_DIR = ./libs

LIBFT = $(LIB_DIR)/libft
FT_PRINTF = $(LIB_DIR)/ft_printf

# compiler option
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I $(INC_DIR)\
		   -I $(LIBFT)/includes\
		   -I $(FT_PRINTF)/includes\

LIBS = -L $(LIBFT) -lft\
	   -L $(FT_PRINTF) -lftprintf\

# srcs
SRCS = list.c\
	   sort.c\
	   context.c\
	   print_detail.c\
	   print_list.c\
	   parse_flags.c\
	   compare.c\
	   directory_entry.c\
	   aggregate.c\
	   tty.c\
	   visit.c\
	   classified_list.c\
	   error.c\
	   utils.c\

SRC_MAIN = main.c

TESTS = *.test.cpp

# compile
HEADERS = $(INC_DIR)/ft_ls.h\
		  $(LIBFT)/includes/libft.h\
		  $(FT_PRINTF)/includes/ft_printf.h\
		  $(FT_PRINTF)/includes/bigint.h\
		  $(FT_PRINTF)/includes/fixedpoint.h\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_MAIN:.c=.o))
OBJS += $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# commands
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(FT_PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(OBJS) -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

def = ''

test: $(addprefix $(SRC_DIR)/, $(SRCS)) $(SRC_DIR)/$(TESTS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(FT_PRINTF)
	g++\
		-Wall -Wextra -std=c++11\
		$(def)\
		-lgtest\
		$(LIBS)\
		$(INCLUDES)\
		$(addprefix $(SRC_DIR)/, $(SRCS)) $(SRC_DIR)/$(TESTS)\
		-o test

.PHONY: test all clean fclean re
