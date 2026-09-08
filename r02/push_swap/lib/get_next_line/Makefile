# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 23:28:32 by sklaokli          #+#    #+#              #
#    Updated: 2025/04/12 16:12:51 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Libraries
NAME		:=	get_next_line

## Paths to files
SRC_DIR		:=	sources
OBJ_DIR		:=	objects
INC_DIR		:=	include

## Source files
SRC			:=	$(addprefix $(SRC_DIR)/, $(FILES))
FILES		:=	get_next_line.c get_next_line_utils.c

## Include files
INC			:=	-I $(INC_DIR)

## Object files
OBJ			:=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

## Total number of files
COMPILED	:=	0
TOTAL_FILES	:=	$(words $(OBJ))

## Commands
RM			:=	rm -f
CC			:=	cc
LIBC		:=	ar rcs
FLAGS		:=	-Wall -Wextra -Werror

## Color Codes
CYAN		:=	\033[0;36m
GREEN		:=	\033[0;32m
RED			:=	\033[0;31m
BLUE		:=	\033[0;34m
YELLOW		:=	\033[0;33m
RESET		:=	\033[0m

## Targets
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@ mkdir -p $(dir $@)
				@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
				@ PERCENT=$$(($(COMPILED)*100/$(TOTAL_FILES))); \
				echo "$(BLUE)[$(COMPILED)/$(TOTAL_FILES)] Compiling $< ($$PERCENT%)$(RESET)\r"; \
				$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ) Makefile
				@ $(LIBC) $(NAME) $(OBJ)
				@ echo "$(GREEN)[OK] $(NAME) built succesfully.$(RESET)"

clean:
				@ $(RM) -rf $(OBJ_DIR)
				@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean:
				@ $(RM) -rf $(OBJ_DIR) $(NAME)
				@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re:				fclean all

.PHONY:			all clean fclean re