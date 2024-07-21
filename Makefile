# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 18:31:47 by mmuhaise          #+#    #+#              #
#    Updated: 2024/07/18 17:54:45 by mmuhaise         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_B = pipex_bonus

SRCS = main.c utils.c
SRCS_B = pipex_bonus.c utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

LIBFT_DIR = ./libft

LIBFT_LIB = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJS) $(LIBFT_LIB)

bonus:	$(NAME_B)

$(NAME_B):	$(OBJS_B)
			make -C $(LIBFT_DIR)
			cc -Wall -Wextra -Werror -o $(NAME_B) $(OBJS_B) $(LIBFT_LIB)

.c.o:
	cc -Wall -Wextra -Werror -c $< -o $(<:.c=.o)

clean: 	
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re
