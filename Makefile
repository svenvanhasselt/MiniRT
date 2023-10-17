# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/06 17:29:14 by yizhang       #+#    #+#                  #
#    Updated: 2023/10/17 18:39:58 by yizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT
CC = cc
FLAG = -Wall -Werror -Wextra #-g -fsanitize=address
LIBFT := lib/libft
LIBMLX	:= lib/mlx42
LIBS := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
LINK := -I include -lglfw -I $(LIBFT)/includes -I $(LIBMLX)/include/MLX42/
SRC_DIR := src
OBJ_DIR := obj
SRC := \
	main.c \
	parsing.c \
	errors.c \
	color.c \
	render.c\

SRC := $(SRC:%=$(SRC_DIR)/%)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# color 
BOLD		= \033[1m
ITALIC		= \033[3m
UNDER 		= \033[4m
CYAN		= \033[36;1m
GREEN		= \033[32;1m
INDIGO		= \033[38;2;75;0;130m
CORAL		= \033[38;2;255;127;80m
RESET		= \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT)
	@cd	$(LIBMLX) && cmake -B build && cmake --build build -j4
	@$(CC) $(FLAG) $(OBJ) $(LIBS) $(LINK) -o $(NAME)
	@echo "$(BLOD) $(GREEN) Compilation MiniRT Done $(RSET)"

$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAG) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build
	@echo "$(BLOD) $(CYAN) Clean objects Done $(RSET)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(BLOD) $(CYAN) Clean MiniRT Done $(RSET)"

re:fclean all

.PHONY: clean fclean re
	
	
	
