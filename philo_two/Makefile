# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppipes <ppipes@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/03 16:22:35 by ppipes            #+#    #+#              #
#    Updated: 2021/03/30 23:04:44 by ppipes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
SRC = philo_two.c
HEADER = ./philo_two.h
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror 
LIBFLAGS = -pthread

.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJ) $(HEADER)
	gcc $(OBJ) $(LIBFLAGS) $(CFLAGS) -o $(NAME)
%.o: %.c
	gcc $(CFLAGS) -c $<
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME) 
re: fclean all
