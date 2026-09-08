# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/22 14:05:00 by sklaokli          #+#    #+#              #
#    Updated: 2026/09/06 00:35:12 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -I includes

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = includes

SRC_FILES   = main.c \
              push_swap.c \
              action/push.c \
              action/rotate.c \
              action/rrotate.c \
              action/swap.c \
              sort/large.c \
              sort/small.c \
              stack/init.c \
              stack/parse.c \
              stack/utils.c \
              utils/cleanup.c \
              utils/parser.c

HEADER_FILES = push_swap.h stack.h action.h sort.h utils.h

SRCS        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
HEADERS     = $(addprefix $(INC_DIR)/, $(HEADER_FILES))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re