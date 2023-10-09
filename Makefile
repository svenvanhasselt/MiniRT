# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/06 17:29:14 by yizhang       #+#    #+#                  #
#    Updated: 2023/10/09 18:22:42 by yizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT
CC = gcc
FLAG = -Wall -Werror -Wextra
MLX = mlx42/build/libmlx42.a
LINK = -Iinclude -lglfw
SRC_DIR = src
SRC = main.c
OBJ_DIR = obj
OBJ = $(addprefix /, $(notdir $(SRC:.c=.o)))

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

$(NAME):$(OBJ_DIR)/$(OBJ)
		@$(CC) $(FLAG) $(OBJ_DIR)/$(OBJ) $(MLX) $(LINK) -o $(NAME)
		@echo "$(BLOD) $(GREEN) Compilation MiniRT Done $(RSET)"

$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAG) -c -o $@ $<

clean:
	@rm -rf $(OBJ_DIR)/$(OBJ)
	@echo "$(BLOD) $(CYAN) Clean objects Done $(RSET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(BLOD) $(CYAN) Clean MiniRT Done $(RSET)"

re:fclean all

.PHONY: clean fclean re
	
	
	