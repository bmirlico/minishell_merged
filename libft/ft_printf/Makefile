# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 19:25:05 by bmirlico          #+#    #+#              #
#    Updated: 2023/02/20 15:26:06 by bmirlico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 			ft_printf.c \
				ft_printf_struct.c \
				ft_printf_fcts1.c \
				ft_printf_fcts2.c \
				ft_printf_len1.c \
				ft_printf_len2.c \
				ft_printf_len3.c \
				ft_printf_len4.c \
				ft_printf_display1.c \
				ft_printf_display2.c \
				ft_printf_display3.c \
				ft_printf_display4.c \
				ft_printf_display5.c \
				ft_printf_display6.c \
				ft_printf_display7.c \
				ft_printf_display8.c \
				ft_printf_flags1.c \
				ft_printf_flags2.c \
				ft_printf_flags3.c

OBJS = 			$(SRCS:.c=.o)

NAME = 			libftprintf.a

CC = 			cc

CFLAGS = 		-Wall -Wextra -Werror

RM = 			rm -f

all:			$(NAME)

$(NAME): 		$(OBJS)
				ar rcs $(NAME) $(OBJS)

bonus:			all

clean:	
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re bonus
