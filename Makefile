# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plamusse <plamusse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/17 14:39:22 by plamusse          #+#    #+#              #
#    Updated: 2017/08/20 14:47:02 by plamusse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fillit

# directories
SRC_DIR		= ./src
INC_DIR		= ./includes
OBJ_DIR		= ./obj
LIB_DIR		= ./lib

# src / obj files

SRC			= main.c \
			  solve.c \
			  load.c
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# compiler and flags
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

# libraries
L_FT		= $(LIB_DIR)/libft
LIB_LNK		= -L $(L_FT) -lft
LIB_INC		= $(L_FT)/includes

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIB_INC) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(MAKE) -C $(L_FT)
	$(CC) -o $@ $(OBJ) $(LIB_LNK)

clean:
	@$(MAKE) clean -C $(L_FT)
	rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) fclean -C $(L_FT)
	rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all
