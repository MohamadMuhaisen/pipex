# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 18:31:47 by mmuhaise          #+#    #+#              #
#    Updated: 2024/07/16 18:15:11 by mmuhaise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft

LIBFT_LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJS) $(LIBFT_LIB)

.c.o:
	cc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

clean: 	
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
