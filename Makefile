# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/05 10:28:43 by aerrazik          #+#    #+#              #
#    Updated: 2023/09/21 17:20:41 by atouba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++
GFC = -Wall -Werror -Wextra -std=c++98 #-g3 -fsanitize=address
NAME = ircserv
SRC =	main.cpp \
		tools.cpp \
		server/ircserv.cpp \
		client/client.cpp \
		client/client_init.cpp \
		channel/Channel.cpp \
		command/command.cpp \
		command/NICK.cpp \
		command/JOIN.cpp \
		command/USER.cpp \
		command/PRIVMSG.cpp \
		command/WHOIS.cpp \
		command/MODE.cpp \
		command/KICK.cpp

OBJS = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(SRC)
	@echo "\033[33mCompiling IRCSERV ...\033[0m"
	@$(CC) $(GFC) $(SRC) -o $(NAME)
	@echo "\033[32mIRCSERV is ready to use !\033[0m"

%.o:%.cpp
	@$(CC) $(GFC) -c $< -o $@

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all
