DEFAULT = \033[0;39m
RED = \033[0;91m
GREEN = \033[0;92m

NAME = philo
GCCFLG = gcc -Wall -Wextra -Werror -I .philosopher.h

SRCS = philo_utils.c philosopher.c

OBJ = ./objs

OBJS = $(addprefix $(OBJ)/, ${SRCS:.c=.o})

all: $(NAME)

$(NAME): ${OBJS}
	@$(GCCFLG) -o $(NAME) $(OBJS) #-fsanitize=address -g
	@echo "$(GREEN)Philo is up to date!${DEFAULT}"

$(OBJ)/%.o: ./%.c
	@mkdir -p ${OBJ}
	@$(GCCFLG)  -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "${RED}Making Clean 🗑️${DEFAULT}"

fclean:
	@rm -rf $(OBJ)
	@rm -rf $(NAME)
	@echo "${RED}Making Fclean 🗑️${DEFAULT}"

re: fclean all