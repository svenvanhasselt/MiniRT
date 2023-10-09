# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: yizhang <yizhang@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2023/10/06 17:29:14 by yizhang       #+#    #+#                  #
#    Updated: 2023/10/09 17:52:48 by yizhang       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT
CC = gcc
FLAG = -Wall -Werror -Wextra
MLX = mlx42/build/libmlx42.a
SRC_DIR = src
SRC = main.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME):$(OBJ_DIR)/$(OBJ)
		$(CC) $(FLAG) $(OBJ_DIR)/$(OBJ) $(MLX) -o $(NAME)

$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAG) -c -o $@ $<

clean:
	rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re:fclean all

.PHONY: clean fclean re
	
	
	