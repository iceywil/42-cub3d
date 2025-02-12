# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2025/02/12 10:21:10 by kimnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   cub3d

CC          =   cc

FLAG        =   -g3 -Wall -Wextra -Werror -lm
 
MLX_PATH	=	minilibx-linux

MLX_MAKE	=	make -C $(MLX_PATH)

FLAG_MLX	=   -L$(MLX_PATH) -lmlx -lX11 -lXext -O3

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

H_FILES		=	cub3d.h cub3d_def.h

C_FILES     =   main.c \
				00_parsing.c 00_save_map.c 00_check_map.c \
				01_mini_carte.c 01_display.c 01_background.c raycasting.c\
				fdf_segment.c fdf_bresenham.c\
				free.c \
				utils.c init.c\
				events_handler.c \

all:        $(NAME)

update:
	@git submodule update --init --recursive

OBJS    =   $(C_FILES:%.c=obj/%.o) $(PARSING:%.c=obj/%.o)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME):    $(LIBFT_LIB) $(H_FILES) $(OBJS)
	@$(MLX_MAKE)
	@$(CC) $(OBJS) $(FLAG) $(FLAG_MLX) $(LIBFT_LIB) -o $(NAME)
	@echo "\033[1;32m""🎉 compilation of $(NAME): ""SUCCESS !🎉""\033[0m"
clean:
	$(MLX_MAKE) clean
	make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS)
	@rm -rf obj

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

obj/%.o : %.c | obj
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj

re:         fclean all

.PHONY:     all clean fclean re
