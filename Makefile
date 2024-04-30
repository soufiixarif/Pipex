NAME = pipex
B_NAME = pipex_bonus
SRC_D = mandatory
B_SRC_D = bonus
SRC = $(SRC_D)/pipex.c $(SRC_D)/libftfun.c $(SRC_D)/libftfun2.c $(SRC_D)/libftfun3.c $(SRC_D)/childes.c
B_SRC = $(B_SRC_D)/pipex_bonus.c $(B_SRC_D)/libftfun_bonus.c $(B_SRC_D)/libftfun2_bonus.c $(B_SRC_D)/libftfun3_bonus.c $(B_SRC_D)/utils_bonus.c
OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	rm -rf $(OBJ)

$(SRC_D)/%.o: $(SRC_D)/%.c $(SRC_D)/pipex.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(B_SRC_D)/%.o: $(B_SRC_D)/%.c $(B_SRC_D)/pipex_bonus.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(B_OBJ)

fclean: clean
	rm -f $(NAME) $(B_NAME)

re: fclean all

bonus : $(B_OBJ)
	$(CC) $(FLAGS) $(B_OBJ) -o $(B_NAME)
	rm -rf $(B_OBJ)