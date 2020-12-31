/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:12:20 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/29 00:19:29 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_lefts(int width, int putlen, char *s)
{
	int		res;

	res = ft_putstrl(s, putlen);
	while ((width - putlen) > 0)
	{
		res += ft_putchar(' ');
		width--;
	}
	return (res);
}

int		ft_leftzero(int putlen,
					t_args *args, long long d, int padding)
{
	int		res;

	res = 0;
	if (d < 0 && args->flag_zero == 1 && args->has_precision != 1)
	{
		res += ft_putchar('-');
		d *= -1;
	}
	while ((args->alt - putlen) > 0)
	{
		if (args->flag_zero == 1 && args->has_precision != 1)
			res += ft_putchar('0');
		else
			res += ft_putchar(' ');
		args->alt--;
	}
	if (args->has_precision && args->precision == 0 && d == 0)
		return (res);
	if (args->c == 'x' || args->c == 'X' || args->c == 'p')
		return (res + ft_putx(d, padding, args));
	else
		return (res + ft_puti(d, padding, args));
	return (0);
}

int		ft_leftone(int putlen,
					t_args *args, long long d, int padding)
{
	int		res;
	int		i;

	res = 0;
	i = 0;
	if (d < 0)
	{
		res += ft_putchar('-');
		d *= -1;
	}
	if (!(args->has_precision && args->precision == 0 && d == 0))
	{
		if (args->c == 'x' || args->c == 'X' || args->c == 'p')
			i = ft_putx(d, padding, args);
		else
			i = ft_puti(d, padding, args);
	}
	while ((args->alt - putlen) > 0)
	{
		res += ft_putchar(' ');
		args->alt--;
	}
	if (args->has_precision && args->precision == 0 && d == 0)
		return (res);
	return (res + i);
}

int		ft_put_conv(t_args *args, va_list ap)
{
	int i;

	i = 0;
	if (args->c == 's')
		return (ft_put_s(args, ap));
	else if (args->c == '%')
		return (ft_put_per(args));
	else if (args->c == 'c')
		return (ft_put_c(args, ap));
	else if (args->c == 'd' || args->c == 'i')
		return (ft_put_d(args, ap));
	else if (args->c == 'x' || args->c == 'X')
		return (ft_put_x(args, ap));
	else if (args->c == 'p')
		return (ft_put_p(args, ap));
	else if (args->c == 'u')
		return (ft_put_u(args, ap, i));
	return (0);
}

int		ft_printf(const char *format, ...)
{
	char	*itr;
	int		res;
	t_args	args;
	va_list	ap;

	itr = (char *)format;
	if (!itr)
		return (0);
	res = 0;
	va_start(ap, format);
	while (*itr)
	{
		if (*itr == '%')
		{
			itr++;
			itr = read_args(&args, itr, ap);
			res += ft_put_conv(&args, ap);
			continue;
		}
		res += ft_putchar(*itr);
		itr++;
	}
	va_end(ap);
	return (res);
}
