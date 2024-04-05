# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 14:33:21 by snegi             #+#    #+#              #
#    Updated: 2024/04/04 12:55:37 by teichelm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -I. -g

LDFLAG		=	-lreadline -lhistory

HEADER	 	=	minshell.h

SRCS		=	minishell.c minishell_utl.c

LIBFT		=	libft.a

OBJS		=	$(SRCS:.c=.o)

all:			$(NAME)

# FUNC_SRCS	=	ft_strncmp.c ft_split.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_substr.c
# FUNC_DIR	=	functions/
# FUNC 		=	$(addprefix $(FUNC_DIR), $(FUNC_SRCS))
# OBJF		=	$(FUNC:.c=.o)

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