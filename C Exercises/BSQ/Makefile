# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 13:21:43 by ddemarco          #+#    #+#              #
#    Updated: 2022/03/03 13:21:47 by ddemarco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = gcc

FLAG = -c -Wall -Werror -Wextra

SRC = ft_file.c ft_map.c ft_solver.c ft_solver_utils.c ft_utils.c ft_validate.c main.c 

OBJ = ft_file.o ft_map.o ft_solver.o ft_solver_utils.o ft_utils.o ft_validate.o main.o

HDR = struct_map.h

RM = rm -f

all: $(NAME)

$(NAME):
	@$(CC) $(FLAG) $(SRC) $(HDR)
	@$(CC) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all