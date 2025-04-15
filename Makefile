# Files:
NAME        =   fractol
D_MANDITORY =   mandatory
HEADER      =   $(D_MANDITORY)/fractol_header.h
FILES_C		=   fractol_main.c
FUNCS       =   $(FILES_C)
FILES       =   $(addprefix $(DIR)/, $(FUNCS))
S_OBJS      =   $(FILES:.c=.o)

CLIENT      =   client

C_FILES     =   $(addprefix minitalk/, )
FUNC        =   $($C_FILES) ft_utils.c ft_atoi.c  client_main.c
C_OBJS      =   $(C_FILES:.c=.o)

# Files_bonus:
HEADER_B    =   minitalk_bonus/minitalk_bonus.h

SERVER_B    =   server_bonus
S_FILES_B   =   minitalk_bonus/ft_utils_bonus.c minitalk_bonus/server_main_bonus.c
S_OBJS_B    =   $(S_FILES_B:.c=.o)

CLIENT_B    =   client_bonus
C_FILES_B   =   minitalk_bonus/ft_utils_bonus.c minitalk_bonus/ft_atoi_bonus.c minitalk_bonus/client_main_bonus.c
C_OBJS_B    =   $(C_FILES_B:.c=.o)

# Shell commands:
CC      =   cc
FLAGS   =   -Wall -Wextra -Werror
RM      =   rm -f

# mandatory:
all: $(NAME) $(CLIENT)

$(NAME): $(S_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(CLIENT): $(C_OBJS)
	$(CC) $(FLAGS) $^ -o $@

minitalk/%.o: minitalk/%.c $(HEADER)
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
	$(RM) $(S_OBJS) $(C_OBJS) $(S_OBJS_B) $(C_OBJS_B)

fclean: clean
	$(RM) $(NAME) $(CLIENT) $(SERVER_B) $(CLIENT_B)

re: fclean all

.PHONY: clean