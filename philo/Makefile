NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = cc
SRC_DIR = ./srcs
SRC = main.c\
		utils.c\
		init.c\
		init_start.c\
		loop.c\
		monitor.c\
		waiter.c\
		error.c\
		free.c\
		eating.c\

SRCS = $(addprefix $(SRC_DIR), $(SRC))

INC_DIR = ./include
OBJ_DIR = ./objs
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p objs
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
		@rm -f $(OBJS)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
