# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/24 15:39:40 by gjupy             #+#    #+#              #
#    Updated: 2022/10/20 21:33:22 by gjupy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo
CC    = gcc
FLAGS = -Wall -Werror -Wextra -pthread -g
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
		./srcs/take_forks.c \
		./srcs/init_2.c \
		./srcs/checker.c

OBJS = $(SRCS:c=o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libs/libft
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS) $(OBJS_B)
	$(MAKE) -C libs/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libs/libft fclean

re: fclean $(NAME)

inside: $(OBJS) $(LIBFT)
	ar -t $(NAME)

git:
	git add .
	git commit -m "commit"
	git push

.PHONY: all clean fclean re git libft