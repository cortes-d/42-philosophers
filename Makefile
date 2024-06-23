# ANSI color codes for pretty output
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

# Directories
DIR_INC = inc
DIR_SRC = src
DIR_LIBFT = $(DIR_SRC)/libft

# Compilation settings
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(DIR_INC)
RM = rm -f

# Source files for the main project
SRC = 	philo.c \
		data.c \
		thread.c \
		msleep.c \
		time.c \
		death.c \
		fork.c \
		action.c \
		flag.c \
		stop.c

SRC := $(addprefix $(DIR_SRC)/, $(SRC))

# Object files
OBJ = $(SRC:.c=.o)

# Pattern rule for object files
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_LIBFT) -I $(DIR_INC)

# Main compilation rule
all: $(NAME)

# Build the project executable
$(NAME): $(OBJ) libft.a
	@echo "$(COLOR_GREEN)Linking project...$(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJ) -L$(DIR_LIBFT) -lft -o $(NAME)
	@echo "$(COLOR_GREEN)Compilation of $(NAME) completed successfully.$(COLOR_RESET)"

# Compile libft.a if not already present
libft.a:
	@echo "$(COLOR_GREEN)Compiling libft...$(COLOR_RESET)"
	@make -C $(DIR_LIBFT)

# Rule to clean up object files
clean: 
	$(RM) $(OBJ)
	@make clean -C $(DIR_LIBFT)
	@echo "$(COLOR_GREEN)Clean-up completed.$(COLOR_RESET)"

# Rule to fully clean the project (includes removing the library)
fclean: clean
	$(RM) $(NAME)
	$(RM) $(DIR_LIBFT)/libft.a
	@make fclean -C $(DIR_LIBFT)
	@echo "$(COLOR_GREEN)Full clean-up completed.$(COLOR_RESET)"

# Rule to recompile everything from scratch
re: fclean all

# Mark rules as phony (not file names)
.PHONY: all clean fclean re
