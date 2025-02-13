# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: a <a@student.42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2025/02/11 03:11:36 by a                ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   cub3d

CC          =   gcc

FLAG        =   -fsanitize=address -g -g3 -Wall -Wextra -Werror -lm
 
FLAG_MLX	=   -I/opt/X11/include -Lminilibx-linux -lmlx -L/opt/X11/lib -lX11 -lXext -O3

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILES     =   srcs/main.c \
				srcs/parsing.c \
				srcs/save_map.c \
				srcs/check_map.c \
				srcs/free.c \
				srcs/utils.c \
				srcs/init.c \
				srcs/mini_map.c \
				srcs/events_handler.c \
				srcs/ray.c \

all:        $(NAME)

OBJS    =   $(C_FILES:srcs/%.c=obj/%.o)

$(LIBFT_LIB):
	make -C $(LIBFT_PATH)

$(NAME):    $(LIBFT_LIB) $(OBJS)
	@$(CC) $(OBJS) $(FLAG) $(FLAG_MLX) $(LIBFT_LIB) -o $(NAME)
	@echo "\033[1;32m""🎉 compilation of $(NAME): ""SUCCESS !🎉""\033[0m"
clean:
	make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS)
	@rm -rf obj

fclean:     clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)

obj/%.o : srcs/%.c | obj
	@mkdir -p $(dir $@)
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj

re:         fclean all

.PHONY:     all clean fclean re
