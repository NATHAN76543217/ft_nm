# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlecaill <nlecaill@student.le-101.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 16:51:32 by dgascon           #+#    #+#              #
#    Updated: 2020/03/09 18:15:31 by nlecaill         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME			=	ft_nm

PATH_INC		=	includes

PATH_SRC		=	srcs
PATH_OBJ		=	objs
SRC_LIST		= 	nm_main.c get_next_xbytes.c
INCS_LIST		=	nm.h

OBJS			=	$(addprefix $(PATH_OBJ)/, $(SRC_LIST:.c=.o))
OBJS_BONUS		=	$(addprefix $(PATH_OBJ)/, $(BONUS_LIST:.c=.o))
INCS			=	$(addprefix $(PATH_INC)/, $(INCS_LIST))

LIBFT_PATH		=	libft
LIBFT_NAME		=	libft.a
LIBFT_FLAG 		=	-Llibft -lft
LIBFT_LIB 		= 	$(FLAG_FT)
LIBFT_INC		=	$(addprefix $(LIBFT_PATH)/, $(PATH_INC))
LIBFT			=	$(addprefix $(LIBFT_PATH)/, $(LIBFT_NAME))

MINILIBX_PATH	= 	libmlx
MINILIBX_NAME	= 	libmlx.a

CC				=	gcc
INCLUDES		=	-I$(LIBFT_INC)  -I$(PATH_INC)
CFLAGS			=	-Wall -Wextra # REVIEW Add -Werror
C-O				=	$(CC) $(CFLAGS) -D DEBUG=$(DEBUG) $(LIBFT_LIB) $(INCLUDES) -c $< -o $@

DIRS_LIST	= $(shell ls -d srcs/*/ | cut -d'/' -f2)

all $(DEBUG):	$(LIBFT_NAME) $(NAME)
	@ printf "\033[0;38;5;82mCompilation de \033[1mCub3D \033[0;38;5;82mreussis.\n\033[0m"

$(NAME): $(OBJS) $(INCS) comp

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	@ $(shell mkdir -p $(PATH_OBJ) $(addprefix $(PATH_OBJ)/, $(DIRS_LIST)))
	@ printf "\033[0;38;5;198mCompilation de $< ..."
	@ $(C-O)
	@ printf "\r                                                                                          \r\033[0m"

$(LIBFT_NAME):
	@ make -C $(LIBFT_PATH) re
	@ printf "\033[0;38;5;82mCompilation de la \033[1m$@ \033[0;38;5;82mreussis.\n\033[0m"

$(MINILIBX_NAME):
	@ printf "\033[0m"
	@ make -C $(MINILIBX_PATH)
	@ printf "\033[0;38;5;82mCompilation de la \033[1m$@ \033[0;38;5;82mreussis.\n\033[0m"

clean:
	@ /bin/rm -rf $(PATH_OBJ)
	@ make -C $(LIBFT_PATH) clean

cleanperso:
	@ /bin/rm -rf $(PATH_OBJ)

fclean: clean
	@ make -C $(LIBFT_PATH) fclean
	@ /bin/rm -rf $(NAME) ./$(NAME)*
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(PATH_OBJ) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;160mSuppression de \033[1m$(NAME)/$(NAME) ..."
	@ sleep 0.5
	@ printf "\r                                                                                          \r\033[0m"
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour \033[1mCub3D.\n"

comp:
	@ $(CC) $(CFLAGS)  -o $(NAME)  $(OBJS) libft/libft.a 

re: fclean all
