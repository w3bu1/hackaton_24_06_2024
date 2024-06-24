# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrabarij <nrabarij@student.42antanana>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 09:45:09 by nrabarij          #+#    #+#              #
#    Updated: 2024/06/24 09:53:35 by nrabarij         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fanorona

BIN		=	libhck.a

CC		=	cc

RM		=	rm -rf

CFLAG	=	-Wall -Wextra -Werror

DIRSRC	=	./src

SRC		=	hck_error.c\

SRCS	=	$(addprefix $(DIRSRC)/, $(SRC))

OBJS	=	$(SRCS:%.c=%.o)

%.o		:	%.c
			$(CC) $(CFLAG) -c $< -o $@

LINK	=	-L./ -lhck

MAIN	=	$(DIRSRC)/hck.c\

$(NAME)	:	$(SRCS) $(BIN)
			$(CC) $(CFLAG) $(MAIN) $(LINK) -o $(NAME)

$(BIN)	:	$(OBJS)
			ar rcs $(BIN) $(OBJS)

all		:	$(NAME)

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(BIN)
			$(RM) $(NAME)

re		:

.PHONY	:	all clean fclean re
