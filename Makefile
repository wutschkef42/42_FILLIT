
NAME := fillit

# directories
SRC_DIR :=	./src
INC_DIR :=	./includes
OBJ_DIR :=	./obj
LIB_DIR :=	./lib

# src / obj files 
SRC		:=	main.c \
			load.c \
			solve.c
OBJ		:=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

# compiler & flags
CC		:=	gcc
CFLAGS	:=	-Wall -Werror -Wextra
CFLAGS	+=	-O3 -march=native -pipe

# libraries
L_FT	:= $(LIB_DIR)/libft

include $(L_FT)/libft.mk

.PHONY:	all clean fclean re

all:
	mkdir -p $(OBJ_DIR)
	@$(MAKE) -C $(L_FT) --no-print-directory
	@$(MAKE) $(NAME) --no-print-directory

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LIB_INC) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIB_LNK) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all	--no-print-directory

relibs:
	@$(MAKE) -C $(L_FT) re --no-print-directory
	@$(MAKE) re --no-print-directory

