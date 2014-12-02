# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/02 20:00:21 by hhismans          #+#    #+#              #
#    Updated: 2014/12/02 20:01:03 by hhismans         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC =	main.c \
		getinfo.c \


DEL = rm -f

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $(OBJ)
	@ranlib $(NAME)
	@echo
	@echo "make -> $@ created"
	@echo

%.o: %.c
	@gcc -o $@ -c $< -I.
	@echo [36mCompilation of[1m $< [0m[32m done [37m
clean:
	@$(DEL) $(OBJ)
	@echo
	@echo "clean -> .o deleted"
	@echo

fclean: clean
	@$(DEL) $(NAME)
	@echo
	@echo "fclean -> ... and $(NAME) deleted"
	@echo

re: fclean all
	@echo
	@echo "re -> $(NAME) reloaded"
	@echo

.PHONY: all clean fclean re

