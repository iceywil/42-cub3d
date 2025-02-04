# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/09 20:46:06 by codespace         #+#    #+#              #
#    Updated: 2025/02/04 17:24:33 by kimnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        =   cub3d

CC          =   cc

FLAG        =   -g3 -Wall -Wextra -Werror -lm
 
FLAG_MLX	=   -L"/home/kimnguye/sgoinfre/minilibx-linux" -lmlx -lXext -lX11 -O3

LIBFT_PATH  =   libft

LIBFT_FILE  =   libft.a

LIBFT_LIB   =   $(LIBFT_PATH)/$(LIBFT_FILE)

C_FILES     =   main.c \
				parsing.c save_map.c check_map.c\
				free.c \
				utils.c init.c\
				mini_carte.c \
				events_handler.c \


all:        $(NAME)

OBJS    =   $(C_FILES:%.c=obj/%.o)

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

obj/%.o : %.c | obj
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj

re:         fclean all

.PHONY:     all clean fclean re
