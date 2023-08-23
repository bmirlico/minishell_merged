# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 18:44:26 by bmirlico          #+#    #+#              #
#    Updated: 2023/08/23 17:06:46 by bmirlico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## MAIN VARIABLES

NAME = 			minishell

CC = 			cc

CFLAGS = 		-g3 -Wall -Wextra -Werror

RM =			rm -f

RM_RF =			rm -rf

## SOURCES AND LIBS

SRC_DIR = 		./src

SRCS = 			$(SRC_DIR)/main.c \
				$(SRC_DIR)/utils_main.c \
				$(SRC_DIR)/lexer_1.c \
				$(SRC_DIR)/lexer_2.c \
				$(SRC_DIR)/lexer_3.c \
				$(SRC_DIR)/utils_syntax.c \
				$(SRC_DIR)/lexer_list.c \
				$(SRC_DIR)/syntax_error_1.c \
				$(SRC_DIR)/syntax_error_2.c \
				$(SRC_DIR)/parser_1.c \
				$(SRC_DIR)/parser_2.c \
				$(SRC_DIR)/parser_list.c \
				$(SRC_DIR)/var_env_state.c \
				$(SRC_DIR)/expand_substitution.c \
				$(SRC_DIR)/get_expand_info.c \
				$(SRC_DIR)/expand.c \
				$(SRC_DIR)/expand_heredoc.c \
				$(SRC_DIR)/split_expand_1.c \
				$(SRC_DIR)/split_expand_2.c \
				$(SRC_DIR)/clean_post_expand.c \
				$(SRC_DIR)/remove_quote.c \
				$(SRC_DIR)/dup_env.c\
				$(SRC_DIR)/lst_env_utils.c\
				$(SRC_DIR)/exec_1.c \
				$(SRC_DIR)/exec_2.c \
				$(SRC_DIR)/exec_3.c \
				$(SRC_DIR)/pipe.c \
				$(SRC_DIR)/pipe_rdir_1.c \
				$(SRC_DIR)/pipe_rdir_2.c \
				$(SRC_DIR)/rdirs_1.c \
				$(SRC_DIR)/rdirs_1bis.c \
				$(SRC_DIR)/rdirs_2.c \
				$(SRC_DIR)/rdirs_3.c \
				$(SRC_DIR)/utils_exec_1.c \
				$(SRC_DIR)/utils_exec_2.c \
				$(SRC_DIR)/utils_exec_3.c \
				$(SRC_DIR)/builtin.c \
				$(SRC_DIR)/cd.c \
				$(SRC_DIR)/pwd.c \
				$(SRC_DIR)/exit_1.c \
				$(SRC_DIR)/exit_2.c \
				$(SRC_DIR)/exit_3.c \
				$(SRC_DIR)/env.c \
				$(SRC_DIR)/unset.c \
				$(SRC_DIR)/export.c \
				$(SRC_DIR)/export_display.c \
				$(SRC_DIR)/echo.c \
				$(SRC_DIR)/echo_special_case.c \
				$(SRC_DIR)/signals_1.c \
				$(SRC_DIR)/signals_2.c \
				$(SRC_DIR)/reset_signal_1.c \
				$(SRC_DIR)/reset_signal_2.c \

LIBFTDIR = 		./libft

LIBFT =			$(LIBFTDIR)/libft.a

LIBFT_FLAGS = 	-L$(LIBFTDIR) -lft

LREADLINE_FLAGS = -lreadline

## OBJECTS

OBJ_DIR =		./obj

OBJS = 			$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

## HEADERS

HDIR = 			./inc

HD = 			$(HDIR)/minishell.h \
				$(LIBFTDIR)/inc/libft.h \
				$(LIBFTDIR)/inc/get_next_line_bonus.h \
				$(LIBFTDIR)/inc/ft_printf.h \

INC_HD =		-I $(HDIR) -I $(LIBFTDIR)/inc

## RULES

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(INC_HD) $(OBJS) $(LIBFT_FLAGS) $(LREADLINE_FLAGS) -o $@

$(OBJS):		$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HD)
				mkdir -p $(OBJ_DIR)
				$(CC) $(CFLAGS) $(INC_HD) -c $< -o $@

$(LIBFT):
				make -C $(LIBFTDIR)

clean:
				$(RM_RF) $(OBJ_DIR)
				make clean -C $(LIBFTDIR)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(LIBFT)

re:				fclean all

.PHONY: 		all clean fclean re
