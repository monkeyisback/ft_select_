#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 17:12:29 by jgirard           #+#    #+#              #
#    Updated: 2014/01/12 22:43:02 by jgirard          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_select

CFLAGS = -Wall -Wextra -Werror -lncurses

SRCS = main.c text.c list.c

SRCO = $(SRCS:.c=.o)

SRCTC = $(SRCS:.c=.c~)

SRCTM = Makefile~

SRCTH = $(NAME:=.h~)

all: $(NAME)

$(NAME): $(SRCO)
	clang -o $(NAME) $(CFLAGS) $(SRCO)

$(SRCO):
	clang -c $(SRCS)

clean:
	/bin/rm -f $(SRCO)

fclean: clean
	/bin/rm -f $(NAME)

aclean: clean fclean
	/bin/rm -f $(SRCTC)
	/bin/rm -f $(SRCTM)
	/bin/rm -f $(SRCTH)

re: fclean all
