# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/06 17:29:14 by yizhang       #+#    #+#                  #
#    Updated: 2023/10/10 13:10:54 by svan-has      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT
CC = gcc
FLAG = -Wall -Werror -Wextra
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

all: libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJ)
	@$(CC) $(FLAG) $(OBJ) $(MLX) $(LIBS) $(LINK) -o $(NAME)
	@echo "$(BLOD) $(GREEN) Compilation MiniRT Done $(RSET)"

$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAG) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)/$(OBJ)
	@$(MAKE) -C $(LIBFT) clean
	@echo "$(BLOD) $(CYAN) Clean objects Done $(RSET)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@echo "$(BLOD) $(CYAN) Clean MiniRT Done $(RSET)"

re:fclean all

.PHONY: clean fclean re
	
	
	
