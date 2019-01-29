NAME := printf

#LIB_DIR := ./libft/
SRC_DIR := ./src/
OBJ_DIR := ./objects/
INC_DIR := ./include/

SRCS := main.c
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

CC := gcc
#FLAGS := -Wall -Wextra -Werror

#LIBFT = $(LIB_DIR)libftprintf.a
#LIBFT_FLAGS := -L $(LIB_DIR) -lft
#LIBFT_INC := $(LIB_DIR)includes

HDR_FLAGS := -I $(INC_DIR) # $(LIBFT_INC) -I $(INC_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(FLAGS) $(HDR_FLAGS) -o $(NAME) $(LIBFT)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $< -o $@ $(FLAGS) $(HDR_FLAGS)

#$(LIBFT):
#	make -C $(LIB_DIR)

clean:
#	make clean -C $(LIB_DIR)
	rm -f $(OBJ)

fclean:
#	make fclean -C $(LIB_DIR)
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all
