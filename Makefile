# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sven <sven@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 17:29:14 by yizhang           #+#    #+#              #
#    Updated: 2024/02/03 14:59:36 by sven             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MiniRT
CC = cc
FLAG = #-Wall -Werror -Wextra
LIBFT := lib/libft
LIBMLX	:= lib/mlx42
LIBS := $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a
LINK := -I include -lglfw -I $(LIBFT)/includes -I $(LIBMLX)/include/MLX42/
MACLINK := -Iinclude -ldl -lglfw -L"/opt/homebrew/lib/"
HEADER := minirt.h
SRC_DIR := src
OBJ_DIR := obj
DIR_DUP = mkdir -p $(@D)
SRC := \
	color/color.c \
	color/tools.c \
	color/objects.c \
	color/inter_shadow.c \
	intersection/hit_object.c\
	intersection/hit_plane.c\
	intersection/hit_sphere.c\
	intersection/hit_cylinder.c\
	intersection/hit_cylinder_caps.c\
	intersection/hit_cone.c\
	intersection/math.c\
	parsing/parsing.c \
	parsing/tools.c \
	parsing/objects.c \
	parsing/checks.c \
	parsing/data.c \
	parsing/errors.c \
	rotation/rotation.c\
	rotation/tools.c\
	rotation/translation.c\
	tools/errors.c \
	tools/keys.c\
	tools/setter.c\
	tools/tools.c\
	tools/vector.c\
	tools/vector_util.c\
	main.c \

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

$(NAME): $(OBJ) $(HEADER)
	@$(MAKE) -C $(LIBFT)
	@cd	$(LIBMLX) && cmake -B build && cmake --build build -j4
	@$(CC) $(FLAG) $(OBJ) $(LIBS) $(LINK) -lm -o $(NAME)
	@echo "$(BLOD) $(GREEN) Compilation MiniRT Done $(RSET)"

$(OBJ_DIR)/%.o: ./$(SRC_DIR)/%.c
	@$(DIR_DUP)
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
	
	
	
