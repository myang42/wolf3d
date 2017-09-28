# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: myang <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/11 17:49:44 by myang             #+#    #+#              #
#    Updated: 2017/09/28 16:43:39 by myang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Wolf3D
INCLS_D = includes
OBJS_D = objs
SRCS_D = srcs
LIBFT_D = libft
MLX_D = minilibx_macos
FLAGS = -g -Wall -Wextra -Werror
INCLS = -I includes/
LIBFT = -L $(LIBFT_D) -lft
MLX = -L $(MLX_D) -lmlx -framework OpenGL -framework Appkit
CC = gcc $(FLAGS) $(INCLS)

SRCS_F = ceilling_floor_text\
		 clear_data\
		 dmg\
		 draw\
		 init_pos\
		 init\
		 keyfcnt\
		 keyfcnt_mr\
		 main\
		 map_error\
		 minimap\
		 music\
		 raycast\
		 readfile\
		 secur_data\
		 sprite\
		 texturing\
		 wall_text_color

OBJS = $(SRCS_F:%=$(OBJS_D)/%.o)
SRCS = $(SRCS_F:%=$(SRCS_D)/%.c)

all : $(NAME)

$(OBJS_D):
	mkdir -p $@
	@echo "\\0033[2;32mOBJS_DIR CREATED :\\0033[0m $@"
	@echo "CREATED :"

$(OBJS_D)/%.o: $(SRCS_D)/%.c
	@$(CC) -c $< -o $@
	@echo "\\0033[1;34m- $@\\0033[0m"

$(NAME) : $(OBJS_D) $(SRCS)
	@$(MAKE) -j -s $(OBJS)
	@echo "\\0033[1;32mMake recalls itself\\0033[0m"
	@make -j -s -C $(LIBFT_D)
	@make -j -s -C $(MLX_D)
	@$(CC) $(LIBFT) $(OBJS) $(MLX) -o $@
	@echo "\\0033[1;33m< $(NAME) > CREATED\\0033[0m"

clean :
	@rm -rf $(OBJS_D)
	@make clean -C $(LIBFT_D)
	@echo "\\033[0;33mOBJS from < $(LIBFT_D) > DELETED\\033[0m" 
	@echo "\\0033[0;33mOBJS from < $(NAME) > DELETED\\0033[0m"

fclean : clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_D)
	@echo "\\0033[0;33mThe file < $(NAME) > IS DELETED\\0033[0m"

re : fclean all

.PHONY : all clean fclean re
