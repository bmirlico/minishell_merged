/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 19:42:34 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:51:39 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONVERTERS "cspdiuxX"

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

/* 1. Structure et toutes les fonctions qui alimentent la structure */

typedef struct s_options
{
	int		minus;
	int		zero;
	int		width;
	int		point;
	int		precision;
	int		sharp;
	int		plus;
	int		space;
}	t_options;

typedef void	(*t_ptr_func)(va_list, int *, int *, t_options *);

void	set_struct(const char *s, t_options *ptr, int *i);

void	init_flags(const char *s, t_options *ptr, int *i);

void	count_width(const char *s, t_options *ptr);

void	count_precision(const char *s, t_options *ptr);

void	init_zero(t_options *ptr);

int		ftm_strchr(const char *s, char c);

/* 2. Organisation de printf,
	avec toutes les fonctions du tableau de fonctions */

int		get_index(char *s, char c);

void	get_arg(const char *flag_string, va_list p, int *count, int *i);

int		ft_printf(const char *format, ...)
		__attribute__ ((format (printf, 1, 2)));

void	ft_putchar_ptr(char c, int *count, int *i);

void	ft_putchar_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_putstr_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_putptr_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_putdecimal_s_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_putint_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_putdecimal_us_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_puthexa_min_pf(va_list p, int *count, int *i, t_options *ptr);

void	ft_puthexa_maj_pf(va_list p, int *count, int *i, t_options *ptr);

/* 3. Fonctions de calcul de longueur de la chaine de caractere */

void	*ft_calloc_zero(size_t nmemb, size_t size);

void	ft_bzero(void *s, size_t n);

int		count_param(long long n);

int		count_param_x(long long n);

int		count_param_ux(unsigned long n);

int		ftm_strlen(char *s);

int		calcul_len_d(t_options *ptr, int count_arg, long long n);

int		calcul_len_u(t_options *ptr, int count_arg, unsigned long n);

int		calcul_len_x(t_options *ptr, int count_arg, long long n);

int		calcul_len_s(t_options *ptr, int len_str, char *str);

int		calcul_len_s_minus(t_options *ptr, int len_str);

int		calcul_len_s_right(t_options *ptr, int len_str);

size_t	ft_max(int a, int b);

size_t	ft_min(int a, int b);

int		is_neg(long long n);

int		is_zero(long long n);

int		is_plus_neg(long long n, t_options *ptr);

int		is_plus_neg_u(unsigned long n, t_options *ptr);

/* 4. Fonctions d'affichage de la chaine de caractere */

void	ft_conditions_flags(t_options *ptr, char *s, int count_param,
			long long n);

void	ft_conditions_dminus(t_options *ptr, char *s, int count_param,
			long long n);

void	ft_conditions_dright(t_options *ptr, char *s, int count_param,
			long long n);

void	ft_conditions_dright2(t_options *ptr, char *s, int count_param,
			long long n);

void	ft_conditions_flags_str(t_options *ptr, char *s, int len_str,
			char *str);

void	ft_conditions_flags_ptr(t_options *ptr, char *s, int len_nb);

void	put_zero_left(char *s, int pos, int add);

void	put_space_left(char *s, int add);

void	put_space_right(char *s, int pos, int add);

void	put_sub_s(char *s, int pos, char *str, int add);

void	put_in_array_c(char *array, char c, t_options *ptr);

void	put_in_array(char *array, char *nb_str, long long n, t_options *ptr);

void	put_d_minus(t_options *ptr, char *array, char *nb_str, long long n);

int		put_d_minus_pr(t_options *ptr, int len_nb, long long n);

void	put_d_right(t_options *ptr, char *array, char *nb_str, long long n);

void	put_in_array_str(char *array, int len_str, char *str, t_options *ptr);

void	put_in_array_strnl(t_options *ptr, char *array, char *str_n, int len);

void	put_in_array_strnl_minus(t_options *ptr, char *array, char *str_n);

void	put_in_array_strnl_right(t_options *ptr, char *array, char *str_n,
			int len);

void	put_in_array_str_minus(t_options *ptr, char *array, char *str,
			int len_str);

void	put_in_array_str_right(t_options *ptr, char *array, char *str,
			int len_str);

void	put_in_array_ptr(char *array, char *hexa_str, unsigned long hexa,
			t_options *ptr);

void	put_in_array_ptrn(char *array, char *nil, t_options *ptr, int len);

void	put_in_array_ptr_minus(char *array, char *hexa_str, int len);

void	put_in_array_ptr_right(char *array, char *hexa_str, int len,
			int len_nb);

void	put_in_array_u(char *array, char *nb_str, unsigned long n,
			t_options *ptr);

void	put_u_minus(t_options *ptr, char *array, char *nb_str, unsigned long n);

int		put_u_minus_pr(t_options *ptr, int len_nb, unsigned long n);

void	put_u_right(t_options *ptr, char *array, char *nb_str, unsigned long n);

void	put_in_array_xx(char *array, char *nb_str, unsigned long n,
			t_options *ptr);

char	*ftm_itoa(long long n);

char	*ftm_strdup(char *s);

char	*ft_itoa_u(long long n);

char	*ft_itoa_ux(unsigned long n);

char	*ft_itoa_x(long long n);

char	*ft_itoa_xx(long long n);

void	ft_putstr_count(char *s, int *count);

void	ft_putstr_c(char *s, int *count, int len);

void	double_free(void *ptr, void *ptr1);

/* 5. Gestion du '-' des nb negatifs et des bonus 2 (flags +, ' ', et #) */

void	ft_swap(char *c1, char *c2);

void	put_plus_d(t_options *ptr, char *array, int len_nb, long long n);

void	put_space_d(t_options *ptr, char *array, int len_nb, long long n);

void	put_neg_d(t_options *ptr, char *array, int len_nb);

void	put_plus_u(t_options *ptr, char *array, int len_nb, unsigned long n);

void	put_space_u(t_options *ptr, char *array, int len_nb, unsigned long n);

void	put_sharp_x(t_options *ptr, char *array, int len_nb);

void	put_sharp_minus(t_options *ptr, char *array, int len_nb);

void	put_sharp_right(t_options *ptr, char *array, int len_nb);

void	put_sharp_xx(t_options *ptr, char *array, int len_nb);

void	put_sharp_xminus(t_options *ptr, char *array, int len_nb);

void	put_sharp_xright(t_options *ptr, char *array, int len_nb);

#endif
