# Files:
NAME        =   fractol
ROOT_DIR    =   mandatory
HEADER      =   $(ROOT_DIR)/fractol_header.h
# MAIN_C		=   $(ROOT_DIR)/fractol_main.c
FUNCS_C     =   fractol_args_parcing.c fractol_atof.c fractol_hooks.c fractol_initialization.c fractol_manual_exit.c fractol_render.c fractol_sets.c utils_exit.c utils_libft.c fractol_main.c
FILES       =   $(addprefix $(ROOT_DIR)/, $(FUNCS_C))
OBJS        =   $(FILES:.c=.o)

# Shell commands:
CC      =   cc
FLAGS   =   -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit
RM      =   rm -f

# mandatory:
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS)  $^ -o $@

functions/%.o: functions/%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

# Bonus:
bonus: $(SERVER_B) $(CLIENT_B)

$(SERVER_B): $(S_OBJS_B)
	$(CC) $(FLAGS) $^ -o $@

$(CLIENT_B): $(C_OBJS_B)
	$(CC) $(FLAGS) $^ -o $@

minitalk_bonus/%_bonus.o: minitalk_bonus/%_bonus.c $(HEADER_B)
	$(CC) $(FLAGS) -c $< -o $@

# Rules:
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean