# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 15:39:40 by gjupy             #+#    #+#              #
#    Updated: 2022/10/17 12:11:08 by gjupy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo
CC    = gcc
FLAGS = -Wall -Werror -Wextra -pthread
LIBFT = ./libs/libft/libft.a
SRCS  = ./srcs/main.c \
		./srcs/parser_errors.c \
		./srcs/error.c \
		./srcs/init.c \
		./srcs/threads.c \
		./srcs/print.c \
		./srcs/actions.c \
		./srcs/free.c \
		./srcs/utils.c \
		./srcs/checker.c

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libs/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

git:
	git add .
	git commit -m "commit"
	git push

.PHONY: all clean fclean re git libft