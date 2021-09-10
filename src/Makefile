# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlecaill <nlecaill@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 16:51:32 by nlecaill          #+#    #+#              #
#    Updated: 2021/09/10 00:30:40 by nlecaill         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

.PHONY:	all clean fclean re

NAME			=	ft_nm

PATH_INC		=	includes
LIBFT_PATH		=	libft
PATH_SRC		=	srcs
PATH_OBJ		=	objs


SRC_LIST		= 	nm_main.c ft_phdr.c	\
					ft_symbols.c ft_sym_lst.c utils.c interp_ar.c

INCS_LIST		=	nm.h 

OBJS			=	$(addprefix $(PATH_OBJ)/, $(SRC_LIST:.c=.o))
OBJS_BONUS		=	$(addprefix $(PATH_OBJ)/, $(BONUS_LIST:.c=.o))
INCS			=	$(addprefix $(PATH_INC)/, $(INCS_LIST))

LIBFT_NAME		=	libft.a
LIBFT_FLAG 		=	-Llibft -lft
LIBFT_INC		=	$(addprefix $(LIBFT_PATH)/, $(PATH_INC))
LIBFT			=	$(addprefix $(LIBFT_PATH)/, $(LIBFT_NAME))

CC				=	gcc
INCLUDES		=	-I$(LIBFT_INC)  -I$(PATH_INC)
CFLAGS			=	-Wall -Wextra -Werror
C-O				=	$(CC) $(CFLAGS) $(LIBFT_FLAG) $(INCLUDES) -c $< -o $@

DIRS_LIST	=	$(shell ls -R srcs 2> /dev/null | grep / | cut -d / -f2-3 | cut -d : -f 1)

all:	init $(LIBFT_NAME) $(NAME)
	@ printf "\033[0;38;5;82mCompilation de \033[1m$(NAME) \033[0;38;5;82mreussis.\n\033[0m"

$(NAME): $(OBJS) $(INCS) comp
		$(CC) $(CFLAGS) $(LIBFT_FLAG) $(INCLUDES) ${OBJS} -o $@ ${LIBFT_PATH}/libft.a

init:
	mkdir -p ${PATH_OBJ}

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c $(INCS)
	@ $(shell mkdir -p $(PATH_OBJ) $(addprefix $(PATH_OBJ)/, $(DIRS_LIST)))
	@ printf "\033[0;38;5;198mCompilation de $< ..."
	@ $(C-O)
	@ printf "\r                                                                                          \r\033[0m"

$(LIBFT_NAME):
	@ make -C $(LIBFT_PATH) 
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
	@ printf "\033[0;38;5;82mSuppression des fichiers de compilation reussis pour \033[1m$(NAME).\n"

comp:
	@ $(CC) $(CFLAGS)  -o $(NAME)  $(OBJS) $(LIBFT_PATH)/$(LIBFT_NAME) 

re: fclean all
