NAME := minirt
CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBFT	:= ./library/libft
HEADERS := -I $(LIBFT)/includes -I includes
LIB	:= $(LIBFT)/libft.a
SRC_DIR := source
OBJ_DIR := object
SRC := \
		main.c\
		
SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DIR_DUP = mkdir -p $(@D)
RM := rm -rf

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) $(HEADERS) -o $(NAME) $(READLINEFLAGS)
	$(info MiniRT Compiled)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -c -o $@ $^ $(HEADERS) 

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all libft clean fclean re