# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yuewang <yuewang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 15:50:42 by yuewang           #+#    #+#              #
#    Updated: 2024/01/25 18:06:59 by yuewang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########## ARGUMENTS ###########

NAME	  = pipex
CC		  = cc
CFLAG	  = -Wall -Wextra -Werror
INC_LIBFT = -I src/libft/
INC		  = -I inc/
RM		  = rm -f

########## SOURCES ###########

LIBFT_DIR 	= src/libft/
LIBFT		= $(LIBFT_DIR)libft.a

SRC_DIR    = src/
SRC_FILES	= $(SRC_DIR)pipex.c $(SRC_DIR)pipe.c \
				$(SRC_DIR)path.c $(SRC_DIR)error_handler.c $(SRC_DIR)execute.c

OBJ_DIR    = obj/
OBJ 	   = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

########## RULES ###########

all : $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAG) $(INC) $(INC_LIBFT) -c $< -o $@

clean :
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean_libft :
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean : clean fclean_libft
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re fclean_libft