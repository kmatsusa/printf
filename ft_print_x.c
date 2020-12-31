/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 20:57:38 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/30 05:23:49 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_put_px(unsigned long long ud, int padding, t_args *args)
{
	int		res;

	res = 0;
	if (args->alt)
	{
		res += write(1, "0", 1);
		return (res);
	}
	while (padding-- > 0)
		res += ft_putchar('0');
	if (ud / 16)
		res += ft_putx(ud / 16, padding, args);
	if ((ud % 16) >= 10)
		res += args->c == 'x' || args->c == 'p' ?
		ft_putchar((ud % 16) - 10 + 'a') : ft_putchar((ud % 16) - 10 + 'A');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int		ft_putx(long long ud, int padding, t_args *args)
{
	int		res;

	res = 0;
	while (padding-- > 0)
		res += ft_putchar('0');
	if (ud / 16)
		res += ft_putx(ud / 16, padding, args);
	if ((ud % 16) >= 10)
		res += args->c == 'x' || args->c == 'p' ?
		ft_putchar((ud % 16) - 10 + 'a') : ft_putchar((ud % 16) - 10 + 'A');
	else
		res += ft_putchar((ud % 16) + '0');
	return (res);
}

int		ft_put_x(t_args *args, va_list ap)
{
	int				precision;
	unsigned int	d;
	int				len;
	int				padding;

	args->alt = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
	d = va_arg(ap, unsigned int);
	len = ft_get_digits_x(d);
	if (args->has_precision && args->precision == 0 && d == 0)
		len = 0;
	padding = (len < precision) ? precision - len : 0;
	if (args->flag_left == 0)
		return (ft_leftzero(len + padding, args, d, padding));
	if (args->flag_left == 1)
		return (ft_leftone(len + padding, args, d, padding));
	return (0);
}

int		ft_put_p(t_args *args, va_list ap)
{
	int					plen;
	int					zero;
	int					space;
	unsigned long long	ptmp;
	unsigned long long	p;
	int					res;

	res = 0;
	p = (unsigned long long)va_arg(ap, void *);
	plen = (!p && args->has_precision && !args->precision) ? 0 : 1;
	if (p == 0 && plen == 1)
		args->alt = 1;
	ptmp = p;
	while ((ptmp /= 16))
		plen++;
	zero = (args->precision < 0 && args->flag_zero == 1)
		? args->precision - plen - 2 : args->precision - plen;
	space = (zero > 0) ? args->width - zero - plen - 2 : args->width - plen - 2;
	if (args->flag_left != 1)
		while (space-- > 0)
			res += write(1, " ", 1);
	res += write(1, "0x", 2);
	while (zero-- > 0)
		res += write(1, "0", 1);
	if (!(args->has_precision && args->precision == 0) || p != 0)
		res += ft_put_px(p, 0, args);
	if (args->flag_left == 1)
		while (space-- > 0)
			res += write(1, " ", 1);
	return (res);
}
