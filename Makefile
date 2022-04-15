NAME := philo

ifdef sanitize
CFLAGS := -Wall -Wextra -fsanitize=thread -g
else
CFLAGS := -Wall -Wextra -Werror -g
endif

CC := gcc

SRC := 			src/main.c \
				src/define_rules.c \
				src/make_philosophers.c \
				src/free_philos.c \
				src/simulation.c \
				src/print_action.c \
				src/gameover.c \
				src/destroy_mutex_rules.c  \
				src/sleep_time.c

UTILS :=		utils/ft_atoi.c \
				utils/check_string_numerical.c

OBJ_DIR :=		obj
OBJ :=			$(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o) $(UTILS:%.c=%.o))

INC := -I ./inc

GREEN := 			"\033[1;32m"
CYAN := 			"\033[1;36m"
RED := 				"\033[1;31m"
PURPLE := 			"\033[1;35m"

all : $(NAME)

sanitize : fclean 
	$(MAKE) sanitize=1

$(NAME) : $(OBJ)
	@echo $(GREEN)"Compling philo"
	@$(CC) $(CFLAGS) $(INC) -o $@ $^ 
	@echo $(CYAN)"Philo compiled [OK]"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 

clean : 
	@rm -rf $(OBJ_DIR)
	@echo $(RED)"Cleaning philo [OK]"

fclean : clean
	@rm -rf $(NAME)
	@echo $(RED)"Removing executable and object files [OK]"

re : fclean all

.PHONY : all, clean, fclean, re
