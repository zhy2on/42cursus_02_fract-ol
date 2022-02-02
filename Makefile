# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jihoh <jihoh@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/03 01:01:21 by jihoh             #+#    #+#              #
#    Updated: 2022/02/03 02:23:22 by jihoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -lmlx -framework OpenGL -framework AppKit -Werror -Wextra -Wall

NAME = fractol

SRCS = main.c hook.c fractol.c color.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@printf '\033[32m[ ✔ ] %s\n\033[0m' "done"

clean :
	@rm -rf $(OBJS)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "clean"

fclean : clean
	@rm -rf $(NAME)
	@printf '\033[31m[ ✔ ] %s\n\033[0m' "fclean"

re : fclean all

.PHONY: all clean fclean re