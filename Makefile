# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/11 00:03:30 by agrumbac          #+#    #+#              #
#    Updated: 2017/02/07 02:22:35 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls.c ft_ls_front.c ft_ls_rec.c \
ft_ls_back.c ft_ls_back_sort.c ft_ls_back_args.c


OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

CC = gcc

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

all:${NAME}

${NAME}: ${OBJ}
	@make -C libft/
	@echo Compiling ${NAME}
	@${CC} ${CFLAGS} -Ilibft/includes/ -Llibft/ -lft -I. -o $@ ${OBJ}
	@echo "\033[32mft_ls is ready!\033[0m"

${OBJDIR}/%.o : ./srcs/%.c
	@echo Compiling $@
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} -Ilibft/includes/ -I. -c -o $@ $<

clean:
	@echo clean libft...
	@make -C libft/ clean
	@echo clean objs...
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@echo fclean libft...
	@make -C libft/ fclean
	@echo clean ${NAME}...
	@/bin/rm -f ${NAME} test

test:
	@${CC} -I./libft/includes/ -Llibft/ -lft -I. -g -o ${NAME} \
	$(addprefix srcs/, ${SRC})

re: fclean all

build: ${OBJ}

.PHONY: all clean fclean re test
