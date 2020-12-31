/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:06:42 by kmatsusa          #+#    #+#             */
/*   Updated: 2021/01/01 01:00:50 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_puti(long long d, int padding, t_args *args)
{
	int		res;

	res = 0;
	if (d == -2147483648)
	{
		res += ft_putchar('-');
		while (padding-- > 0)
			res += ft_putchar('0');
		res += ft_putstr("2147483648");
		return (res);
	}
	if (d < 0)
	{
		res += ft_putchar('-');
		d *= -1;
	}
	while (padding-- > 0)
		res += ft_putchar('0');
	if (d / 10)
		res += ft_puti(d / 10, padding, args);
	res += ft_putchar((d % 10) + '0');
	return (res);
}

int		ft_put_d(t_args *args, va_list ap)
{
	int		precision;
	int		d;
	int		len;
	int		padding;

	args->alt = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
	d = va_arg(ap, int);
	len = ft_get_digits(d, args);
	if (args->has_precision && args->precision == 0 && d == 0)
		len = 0;
	if (d < 0)
		padding = ((len - 1) < precision) ? precision - (len - 1) : 0;
	else
		padding = (len < precision) ? precision - len : 0;
	if (args->flag_left == 0)
		return (ft_leftzero(len + padding, args, d, padding));
	else if (args->flag_left == 1)
		return (ft_leftone(len + padding, args, d, padding));
	return (0);
}

int		ft_put_u(t_args *args, va_list ap, int len)
{
	int				precision;
	unsigned int	ud;
	unsigned int	tmp;
	int				padding;

	args->alt = args->has_width ? args->width : 0;
	precision = args->has_precision ? args->precision : 0;
	ud = va_arg(ap, unsigned int);
	tmp = ud;
	len = 1;
	while (tmp /= 10)
		len++;
	if (args->has_precision && args->precision == 0 && ud == 0)
		len = 0;
	padding = (len < precision) ? precision - len : 0;
	if (args->flag_left == 0)
		return (ft_leftzero(len + padding, args, ud, padding));
	if (args->flag_left == 1)
		return (ft_leftone(len + padding, args, ud, padding));
	return (0);
}
