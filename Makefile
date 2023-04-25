# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlabbiz <rlabbiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/24 14:07:52 by rlabbiz           #+#    #+#              #
#    Updated: 2023/04/24 16:14:51 by rlabbiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-fsanitize=thread -g
NAME		= philo
DEFS		= philo.h
MAIN_FILE	= philo.c
OBJECTS		= philo_ultis.o \
				philo_ultis1.o

.PHONY : all clean fclean re 

%.o : %.c $(DEFS)
	@$(CC) $(CFLAGS) -c -o $@ $<

all : $(NAME)

$(NAME) : $(OBJECTS) $(DEFS) $(MAIN_FILE)
	@$(CC) $(CFLAGS) $(OBJECTS) $(MAIN_FILE) -o $(NAME)
	@echo "\tThe Philo Programm Is Created."

clean :
	@rm -rf *.o
	@echo "\tObject Files Is Removed."

fclean : clean
	@rm -rf $(NAME)
	@echo "\tThe Execuetble File Is Removed."

re : fclean all