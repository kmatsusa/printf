/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_libft2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:02:51 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/29 01:42:18 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isspace(char c)
{
	return (c >= 9 && c <= 13) || (c == 32);
}

int		ft_atoi(char **str)
{
	long long	res;
	long long	max;

	max = 0x7fffffffffffffff;
	res = 0;
	while (ft_isdigit(**str))
	{
		if (res < max - (**str - '0') / 10)
			res = 10 * res + (**str - '0');
		(*str)++;
	}
	return (res);
}

int		ft_get_digits(int d, t_args *args)
{
	int	digits;

	if (args->precision < 0)
		args->has_precision = 0;
	if (d == -2147483648)
		return (11);
	digits = 0;
	if (d < 0)
	{
		digits++;
		d *= -1;
	}
	while (d / 10)
	{
		digits++;
		d /= 10;
	}
	digits++;
	return (digits);
}

int		ft_get_digits_x(unsigned int ud)
{
	int	digits;

	digits = 0;
	while (ud / 16)
	{
		digits++;
		ud /= 16;
	}
	digits++;
	return (digits);
}

int		ft_strlen(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}
