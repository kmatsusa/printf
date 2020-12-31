/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:01:48 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/29 01:33:40 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_put_s(t_args *args, va_list ap)
{
	int		width;
	int		precision;
	int		putlen;
	char	*s;
	int		res;

	width = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
	s = (char *)va_arg(ap, char *);
	if (!s)
		s = "(null)";
	if (args->has_precision)
		putlen = (ft_strlen(s) > precision) ? precision : ft_strlen(s);
	else
		putlen = ft_strlen(s);
	res = 0;
	if (args->flag_left == 1)
		return (ft_lefts(width, putlen, s));
	while ((width - putlen) > 0)
	{
		res += args->flag_zero == 1 ? ft_putchar('0') : ft_putchar(' ');
		width--;
	}
	return (res + ft_putstrl(s, putlen));
}

int		ft_put_per(t_args *args)
{
	int		width;
	int		putlen;
	char	s;
	int		res;

	width = args->has_width ? args->width : 0;
	s = '%';
	putlen = 1;
	if (args->flag_left == 1)
		return (ft_lefts(width, putlen, &s));
	res = 0;
	while ((width - putlen) > 0)
	{
		res += args->flag_zero == 1 ? ft_putchar('0') : ft_putchar(' ');
		width--;
	}
	return (res + ft_putstrl(&s, putlen));
}

int		ft_put_c(t_args *args, va_list ap)
{
	int		width;
	int		putlen;
	char	s;
	int		res;

	width = args->has_width ? args->width : 0;
	s = (char)va_arg(ap, int);
	putlen = 1;
	res = 0;
	if (args->flag_left == 1)
	{
		res += ft_putchar(s);
		while ((width - putlen) > 0)
		{
			res += ft_putchar(' ');
			width--;
		}
		return (res);
	}
	while ((width - putlen) > 0)
	{
		res += args->flag_zero == 1 ? ft_putchar('0') : ft_putchar(' ');
		width--;
	}
	return (res + ft_putchar(s));
}
