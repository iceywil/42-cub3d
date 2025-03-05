# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2025/03/05 11:54:57 by kimnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   cub3d

CC          =   cc

FLAG        =   -g -g3 -Wall -Wextra -Werror -lm

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
				srcs/move_player.c \
				srcs/calc_utils.c \
				srcs/textures.c \
				srcs/draw_loop.c \

C_BONUS		=	bonus/main_bonus.c \
				bonus/parsing_bonus.c \
				bonus/save_map_bonus.c \
				bonus/check_map_bonus.c \
				bonus/free_bonus.c \
				bonus/utils_bonus.c \
				bonus/init_bonus.c \
				bonus/background_bonus.c \
				bonus/pixel_utils_bonus.c \
				bonus/ray_bonus.c \
				bonus/events_bonus.c \
				bonus/map_bonus.c \
				bonus/move_player_bonus.c \
				srcs/calc_utils.c \
				bonus/textures_bonus.c \
				bonus/draw_loop_bonus.c \
				bonus/door_bonus.c \

OBJS	=		$(C_FILES:%.c=obj/%.o)

OBJS_BONUS	=	$(C_BONUS:%.c=obj/%.o)

all:			update $(NAME)

update:
	@git submodule update --init --recursive

bonus:	$(LIBFT_LIB) $(H_FILES) $(OBJS_BONUS)
	@$(MLX_MAKE)
	@$(CC) $(OBJS_BONUS) $(FLAG) $(FLAG_MLX) $(LIBFT_LIB) -o $(NAME)_bonus
	@echo "\033[1;32m""🎉 compilation of $(NAME)_bonus: ""SUCCESS !🎉""\033[0m"

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
	rm -rf $(NAME) $(NAME)_bonus
	make fclean -C $(LIBFT_PATH)

obj/%.o : %.c | obj
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj

re:         fclean all

.PHONY:     all clean fclean re
