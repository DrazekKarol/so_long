# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdrazek <kdrazek@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 14:40:12 by kdrazek           #+#    #+#              #
#    Updated: 2025/05/20 15:38:23 by kdrazek          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = so_long

SRCS = main.c cleaner.c map.c get_next_line_utils.c get_next_line.c player.c render.c

OBJS = $(SRCS:.c=.o)

HEADERS = so_long.h

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR = ./minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
MLX_INC = -I$(MLX_DIR)

all: $(MLX_DIR)/libmlx.a $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(MLX_DIR)/libmlx.a:
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS) $(NAME)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re