# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 14:33:21 by snegi             #+#    #+#              #
#    Updated: 2024/05/09 16:36:33 by teichelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -I. -g

LDFLAG		=	-lreadline -lhistory

HEADER	 	=	minshell.h

SRCS		=	minishell.c minishell_utl.c env.c multi_pipe.c export.c echo.c redirection.c supporting_fun.c execution.c cmd.c expander1.c expander2.c input_check1.c input_check2.c input_check3.c parser1.c parser2.c parser3.c

LIBFT		=	libft.a

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)


%.o: %.c $(HEADER) Makefile
								$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
		cd ./libft && make
		cd ./libft && mv libft.a "../"
		cd ./libft && make fclean

$(NAME):			$(OBJS) $(LIBFT)
								@$(CC) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAG)
clean:	
		rm -rf $(OBJS) $(LIBFT)

fclean:			clean
						rm -rf $(NAME)

re:		fclean all

.PHONY: all clean fclean re
