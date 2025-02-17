# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2025/02/17 12:19:22 by kimnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   cub3d

CC          =   cc

FLAG        =   -fsanitize=address -g -g3 -Wall -Wextra -Werror -lm

MLX_PATH	=	minilibx-linux

MLX_MAKE	=	make -C $(MLX_PATH)

FLAG_MLX	=   -L$(MLX_PATH) -I/opt/X11/include -Lminilibx-linux -lmlx -L/opt/X11/lib -lX11 -lXext -O3

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

H_FILES		=	cub3d.h cub3d_def.h

C_FILES     =   srcs/main.c \
				srcs/parsing.c \
				srcs/save_map.c \
				srcs/check_map.c \
				srcs/free.c \
				srcs/utils.c \
				srcs/init.c \
				srcs/background.c \
				srcs/pixel_utils.c \
				srcs/ray.c \
				srcs/events.c \
				srcs/map.c \

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
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj

re:         fclean all

.PHONY:     all clean fclean re
