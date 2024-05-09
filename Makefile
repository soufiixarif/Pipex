NAME = pipex
B_NAME = pipex_bonus
SRC_D = mandatory
B_SRC_D = bonus
SRC = $(SRC_D)/pipex.c $(SRC_D)/libftfun.c $(SRC_D)/libftfun2.c $(SRC_D)/libftfun3.c $(SRC_D)/childes.c
B_SRC = $(B_SRC_D)/pipex_bonus.c $(B_SRC_D)/libftfun_bonus.c $(B_SRC_D)/libftfun2_bonus.c $(B_SRC_D)/libftfun3_bonus.c\
$(B_SRC_D)/utils_bonus.c $(B_SRC_D)/get_next_line.c $(B_SRC_D)/get_next_line_utils.c
OBJ = $(SRC:.c=.o)
B_OBJ = $(B_SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)


$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32mMAKING SUCCESSFULY ✅\033[0;37m"

$(SRC_D)/%.o: $(SRC_D)/%.c $(SRC_D)/pipex.h Makefile
	@echo "\033[1;35mcompiling $@..."
	@$(CC) $(FLAGS) -c $< -o $@
	@clear

$(B_SRC_D)/%.o: $(B_SRC_D)/%.c $(B_SRC_D)/pipex_bonus.h $(B_SRC_D)/get_next_line.h Makefile
	@echo "\033[1;35mcompiling $@..."
	@$(CC) $(FLAGS) -c $< -o $@
	@clear

clean:
	@rm -f $(OBJ) $(B_OBJ)
	@echo "\033[33mcleaning objects 🧼"

fclean: clean
	@rm -f $(NAME) $(B_NAME)
	@echo "\033[31mremoving exectable file ❌\033[0;37m"

re: fclean all

bonus : $(B_OBJ)
	@$(CC) $(FLAGS) $(B_OBJ) -o $(B_NAME)
	@echo "\033[32mMAKING BONUS SUCCESSFULY ✅\033[0;37m"
.PHONY : clean