# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 16:02:38 by wscherre          #+#    #+#              #
#    Updated: 2025/03/03 15:21:15 by kimnguye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_isascii.c ft_isprint.c ft_strlen.c \
			ft_memset.c ft_bzero.c ft_memcpy.c \
			ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			ft_toupper.c ft_tolower.c ft_strchr.c \
			ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_memcmp.c ft_strnstr.c ft_calloc.c \
			ft_strdup.c ft_atoi.c ft_substr.c \
			ft_strjoin.c ft_strmapi.c ft_strtrim.c \
			ft_itoa.c ft_striteri.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_split.c ft_atol.c ft_free_double_tab.c \
			ft_printf.c ft_print_c.c ft_print_di.c \
			ft_print_formatted.c ft_print_p.c ft_print_s.c \
			ft_print_u.c ft_print_x.c \
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
			ft_lstmap.c ft_lstnew.c ft_lstsize.c \
			ft_gnl.c ft_strcmp.c \
			ft_strncpy.c ft_strcpy.c\
			ft_strndup.c \
			ft_isnumericlli.c \
			ft_ignore_space.c \

OBJS    =   $(SRCS:%.c=obj/%.o)

CC	=	cc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I.

NAME	=	libft.a

all:		$(NAME)

$(NAME):	$(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "\033[1;32m""🎉 compilation of $(NAME): ""SUCCESS !🎉""\033[0m"
clean:
	@$(RM) $(OBJS)
	@rm -rf obj

fclean:		clean
	$(RM) $(NAME)

re:		fclean all

obj/%.o : %.c | obj
	@$(CC) -c $< -o $@

obj:
	@mkdir -p obj
