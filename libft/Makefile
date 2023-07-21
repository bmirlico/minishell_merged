# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:01:18 by bmirlico          #+#    #+#              #
#    Updated: 2023/05/19 16:32:09 by bmirlico         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 			libft.a

CC 		= 			gcc

CFLAGS 	= 			-g3 -Wall -Wextra -Werror

RM 		= 			rm -f

HDIR = 				./inc

LIBFT_SRCDIRC = 	./lft

LIBFT_SRC =			$(LIBFT_SRCDIRC)/ft_atoi.c \
					$(LIBFT_SRCDIRC)/ft_isalpha.c \
					$(LIBFT_SRCDIRC)/ft_itoa.c \
					$(LIBFT_SRCDIRC)/ft_lstdelone.c \
					$(LIBFT_SRCDIRC)/ft_lstnew.c \
					$(LIBFT_SRCDIRC)/ft_memcpy.c \
					$(LIBFT_SRCDIRC)/ft_putendl_fd.c \
					$(LIBFT_SRCDIRC)/ft_strchr.c \
					$(LIBFT_SRCDIRC)/ft_strlcat.c \
					$(LIBFT_SRCDIRC)/ft_strncmp.c \
					$(LIBFT_SRCDIRC)/ft_substr.c \
					$(LIBFT_SRCDIRC)/ft_bzero.c \
					$(LIBFT_SRCDIRC)/ft_isascii.c \
					$(LIBFT_SRCDIRC)/ft_lstadd_back.c \
					$(LIBFT_SRCDIRC)/ft_lstiter.c \
					$(LIBFT_SRCDIRC)/ft_lstsize.c \
					$(LIBFT_SRCDIRC)/ft_memmove.c \
					$(LIBFT_SRCDIRC)/ft_putnbr_fd.c \
					$(LIBFT_SRCDIRC)/ft_strdup.c \
					$(LIBFT_SRCDIRC)/ft_strlcpy.c \
					$(LIBFT_SRCDIRC)/ft_strnstr.c \
					$(LIBFT_SRCDIRC)/ft_tolower.c \
					$(LIBFT_SRCDIRC)/ft_calloc.c \
					$(LIBFT_SRCDIRC)/ft_isdigit.c \
					$(LIBFT_SRCDIRC)/ft_lstadd_front.c \
					$(LIBFT_SRCDIRC)/ft_lstlast.c \
					$(LIBFT_SRCDIRC)/ft_memchr.c \
					$(LIBFT_SRCDIRC)/ft_memset.c \
					$(LIBFT_SRCDIRC)/ft_putstr_fd.c \
					$(LIBFT_SRCDIRC)/ft_striteri.c \
					$(LIBFT_SRCDIRC)/ft_strlen.c \
					$(LIBFT_SRCDIRC)/ft_strrchr.c \
					$(LIBFT_SRCDIRC)/ft_toupper.c \
					$(LIBFT_SRCDIRC)/ft_isalnum.c \
					$(LIBFT_SRCDIRC)/ft_isprint.c \
					$(LIBFT_SRCDIRC)/ft_lstclear.c \
					$(LIBFT_SRCDIRC)/ft_lstmap.c \
					$(LIBFT_SRCDIRC)/ft_memcmp.c \
					$(LIBFT_SRCDIRC)/ft_putchar_fd.c \
					$(LIBFT_SRCDIRC)/ft_split.c \
					$(LIBFT_SRCDIRC)/ft_strjoin.c \
					$(LIBFT_SRCDIRC)/ft_strmapi.c \
					$(LIBFT_SRCDIRC)/ft_strtrim.c

GNL_SRCDIRC = 		./gnl

GNL_SRC =			$(GNL_SRCDIRC)/get_next_line_bonus.c \
					$(GNL_SRCDIRC)/get_next_line_utils_bonus.c

PRINTF_SRCDIRC =	./ft_printf

PRINTF_SRC =		$(PRINTF_SRCDIRC)/ft_printf.c \
					$(PRINTF_SRCDIRC)/ft_printf_struct.c \
					$(PRINTF_SRCDIRC)/ft_printf_fcts1.c \
					$(PRINTF_SRCDIRC)/ft_printf_fcts2.c \
					$(PRINTF_SRCDIRC)/ft_printf_len1.c \
					$(PRINTF_SRCDIRC)/ft_printf_len2.c \
					$(PRINTF_SRCDIRC)/ft_printf_len3.c \
					$(PRINTF_SRCDIRC)/ft_printf_len4.c \
					$(PRINTF_SRCDIRC)/ft_printf_display1.c \
					$(PRINTF_SRCDIRC)/ft_printf_display2.c \
					$(PRINTF_SRCDIRC)/ft_printf_display3.c \
					$(PRINTF_SRCDIRC)/ft_printf_display4.c \
					$(PRINTF_SRCDIRC)/ft_printf_display5.c \
					$(PRINTF_SRCDIRC)/ft_printf_display6.c \
					$(PRINTF_SRCDIRC)/ft_printf_display7.c \
					$(PRINTF_SRCDIRC)/ft_printf_display8.c \
					$(PRINTF_SRCDIRC)/ft_printf_flags1.c \
					$(PRINTF_SRCDIRC)/ft_printf_flags2.c \
					$(PRINTF_SRCDIRC)/ft_printf_flags3.c

##PRINTF_LIB =		$(PRINTF_SRCDIRC)/libftprintf.a

##PRINTF_LIB_FLAGS =	-L$(PRINTF_SRCDIRC) -lftprintf	

SRCS 	=  			$(LIBFT_SRC) \
					$(GNL_SRC) \
					$(PRINTF_SRC)

OBJS	= 			$(SRCS:.c=.o)

## FACULTATIF car les fichiers _bonus de la libft sont deja inclus ds OBJS

##SRCS_BONUS = 		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
##					ft_lstiter.c ft_lstmap.c

##OBJS_BONUS	= 		$(SRCS_BONUS:.c=.o) 

HD = 				$(HDIR)/libft.h \
					$(HDIR)/get_next_line_bonus.h \
					$(HDIR)/ft_printf.h \

all: 				$(NAME)

$(NAME):			$(OBJS)
					ar rcs $(NAME) $(OBJS)

## FACULTATIF

##bonus:				$(OBJS) $(OBJS_BONUS)
##					ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

%.o:				%.c $(HD)
					$(CC) $(CFLAGS) -I $(HDIR) -c $< -o $@

##$(PRINTF_LIB):		
##					make -C $(PRINTF_SRCDIRC)

clean: 
					$(RM) $(OBJS)
##					make clean -C $(PRINTF_SRCDIRC)

fclean: 			clean
					$(RM) $(NAME)
##					$(RM) $(PRINTF_LIB)

re: 				fclean all

.PHONY:				all bonus clean fclean re