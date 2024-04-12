# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roguigna <roguigna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/27 10:42:30 by roguigna          #+#    #+#              #
#    Updated: 2024/04/12 10:25:47 by roguigna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

CC				= cc

CFLAGS 			= -Wall -Wextra -Werror -pthread -g3 -fsanitize=thread

INCLUDE			= -I libft/includes -I includes


##############################  COLORS  ###################################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[3;92m
YELLOW = \033[0;93m
BLUE = \033[3;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


##############################  SOURCES  #####################################

SRC_DIR			= sources

OBJ_DIR			= object

SRC_FILES		= philosophers.c utils.c parsing.c fill_struct.c free_all.c \
				  routine.c utils_2.c monitoring.c

OBJ             = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

##############################  RULES  #######################################

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDE) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${GRAY}Philosophers object files cleaned! ${DEF_COLOR}"

fclean: clean
	@rm -f $(NAME)
	@echo "${YELLOW}Philosophers executable files cleaned! ${DEF_COLOR}"

re: fclean all

.PHONY: all clean fclean re