# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 14:33:21 by snegi             #+#    #+#              #
#    Updated: 2025/11/19 14:55:06 by teichelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -I. -g

LDFLAG		=	-lreadline -lhistory

HEADER	 	=	minshell.h

SRC_DIR= src

FULL_SRC= $(addprefix $(SRC_DIR)/, $(SRCS) )

SRCS		=	minishell_utl.c echo.c check.c modify_env.c parser_helpers.c parse_redirections.c remover.c split_cmds.c unset.c calculate_redirections.c minishell.c supporting_fun.c env.c export.c execution.c redirection.c multi_pipe.c parser.c expander.c
LIBFT		=	libft.a

OBJS		=	$(FULL_SRC:.c=.o)

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
