# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 12:50:47 by sklaokli          #+#    #+#              #
#    Updated: 2025/05/08 13:04:35 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Libraries
NAME		=	push_swap
CHECKER		=	checker
GNL			=	$(GNL_DIR)/get_next_line
GCT			=	$(GCT_DIR)/gct.a

## Paths
SRC_DIR		:=	sources
OBJ_DIR		:=	objects
INC_DIR		:=	include
LIB_DIR		:=	lib
GNL_DIR		:=	$(LIB_DIR)/get_next_line
GCT_DIR		:=	$(LIB_DIR)/gct

## Subdirectories
SUBDIRS			:=	mandatory bonus utils
mandatory_FILES :=	main.c
bonus_FILES     :=	checker.c
utils_FILES     :=	init.c ft_split.c list.c action.c \
					tiny.c butterfly.c sort.c utils.c

## All sources and objects
SRC_FILES	:=	$(foreach dir,$(SUBDIRS), \
				$(addprefix $(SRC_DIR)/$(dir)/,$($(dir)_FILES)))

OBJ_FILES	:=	$(foreach dir,$(SUBDIRS), \
				$(addprefix $(OBJ_DIR)/$(dir)/,$($(dir)_FILES:.c=.o)))

## Optional named groups
SRC_MANDA	:=	$(addprefix $(SRC_DIR)/mandatory/,$(mandatory_FILES))
SRC_BONUS	:=	$(addprefix $(SRC_DIR)/bonus/,$(bonus_FILES))
SRC_UTILS	:=	$(addprefix $(SRC_DIR)/utils/,$(utils_FILES))

OBJ_MANDA	:=	$(addprefix $(OBJ_DIR)/mandatory/,$(mandatory_FILES:.c=.o))
OBJ_BONUS	:=	$(addprefix $(OBJ_DIR)/bonus/,$(bonus_FILES:.c=.o))
OBJ_UTILS	:=	$(addprefix $(OBJ_DIR)/utils/,$(utils_FILES:.c=.o))

## Include
INC			:=	-I$(INC_DIR) -I$(GNL_DIR)/include -I$(GCT_DIR)/include

## Counters for progress
COMPILED	:=	0
TOTAL_FILES	:=	$(words $(OBJ_UTILS) $(OBJ_MANDA))

## Commands
RM			:=	rm -f
CC			:=	cc
FLAGS		:=	-Wall -Wextra -Werror

## Colors
CYAN		:=	\033[0;36m
GREEN		:=	\033[0;32m
RED			:=	\033[0;31m
BLUE		:=	\033[0;34m
YELLOW		:=	\033[0;33m
RESET		:=	\033[0m

## Compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(dir $@)
	@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
	@ PERCENT=$$(($(COMPILED)*100/$(TOTAL_FILES))); \
	echo "$(BLUE)[$(COMPILED)/$(TOTAL_FILES)] Compiling $< ($$PERCENT%)$(RESET)\r"; \
	$(CC) $(FLAGS) $(INC) -c $< -o $@

## Targets
all: $(NAME)

$(NAME): Makefile $(OBJ_UTILS) $(OBJ_MANDA)
	@ $(CC) $(FLAGS) $(OBJ_UTILS) $(OBJ_MANDA) $(INC) -o $(NAME)
	@ echo "$(GREEN)[OK] $(NAME) built succesfully.$(RESET)"

bonus: Makefile lib $(OBJ_UTILS) $(OBJ_BONUS)
	@ $(CC) $(FLAGS) $(OBJ_UTILS) $(OBJ_BONUS) $(GNL) $(INC) -o $(CHECKER)
	@ echo "$(GREEN)[OK] $(CHECKER) built succesfully.$(RESET)"

lib: Makefile
	@ $(MAKE) -sC $(GNL_DIR)
	@ $(MAKE) -sC $(GCT_DIR)

lib_clean:
	@ $(MAKE) -sC $(GNL_DIR) clean
	@ $(MAKE) -sC $(GCT_DIR) clean

lib_fclean:
	@ $(MAKE) -sC $(GNL_DIR) fclean
	@ $(MAKE) -sC $(GCT_DIR) fclean

clean:
	@ $(MAKE) -sC $(GNL_DIR) clean
	@ $(RM) -rf $(OBJ_DIR)
	@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean: clean
	@ $(MAKE) -sC $(GNL_DIR) fclean
	@ $(RM) -f $(NAME) $(CHECKER)
	@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re lib
