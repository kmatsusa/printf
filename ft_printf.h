/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:56:30 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/30 05:30:48 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# define CONV "cspdiuxX"

typedef struct	s_args
{
	int	c;
	int	flag_zero;
	int	flag_left;
	int	width;
	int alt;
	int	has_width;
	int	precision;
	int	has_precision;
}				t_args;

char			*ft_strchr(char *str, char c);
int				ft_putchar(char c);
int				ft_putstr(char *str);
int				ft_putstrl(char *str, int len);
int				ft_isdigit(char c);
int				ft_isspace(char c);
int				ft_atoi(char **str);
int				ft_get_digits(int d, t_args *args);
int				ft_get_digits_x(unsigned int ud);
void			initialize_args(t_args *args);
void			ft_getwidth(char **itr, va_list ap, t_args *args);
void			ft_getprec(char **itr, va_list ap, t_args *args, long i);
int				ft_getchar(char *itr, t_args *args);
char			*read_args(t_args *args, char *itr, va_list ap);
int				ft_strlen(char *s);
int				ft_lefts(int width, int putlen, char *s);
int				ft_put_s(t_args *args, va_list ap);
int				ft_put_per(t_args *args);
int				ft_put_c(t_args *args, va_list ap);
int				ft_puti(long long d, int padding, t_args *args);
int				ft_putx(long long ud, int padding, t_args *args);
int				ft_leftzero(int putlen,
				t_args *args, long long d, int padding);
int				ft_leftone(int putlen,
				t_args *args, long long d, int padding);
int				ft_put_d(t_args *args, va_list ap);
int				ft_put_u(t_args *args, va_list ap, int i);
int				ft_put_x(t_args *args, va_list ap);
int				ft_put_p(t_args *args, va_list ap);
int				ft_put_conv(t_args *args, va_list ap);
int				ft_printf(const char *format, ...);
int				ft_put_px(unsigned long long ud, int padding, t_args *args);

#endif
