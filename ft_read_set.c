/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmatsusa <kmatsusa@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:02:30 by kmatsusa          #+#    #+#             */
/*   Updated: 2020/12/29 01:41:40 by kmatsusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initialize_args(t_args *args)
{
	args->flag_left = 0;
	args->flag_zero = 0;
	args->c = 0;
	args->has_width = 0;
	args->has_precision = 0;
	args->width = 0;
	args->alt = 0;
	args->precision = 0;
}

void	ft_getwidth(char **itr, va_list ap, t_args *args)
{
	long	i;

	if (**itr == '*')
	{
		i = (int)va_arg(ap, int);
		args->has_width = 1;
		if (i < 0)
		{
			args->flag_left = 1;
			args->width = i * -1;
		}
		else
			args->width = i;
		(*itr)++;
		return ;
	}
	args->has_width = 1;
	args->width = ft_atoi(itr);
}

void	ft_getprec(char **itr, va_list ap, t_args *args, long i)
{
	while (**itr == '.' || **itr == '0')
	{
		args->has_precision = 1;
		(*itr)++;
	}
	if (ft_isdigit(**itr) || **itr == '*')
	{
		if (**itr == '*')
		{
			i = (int)va_arg(ap, int);
			if (i >= 0)
			{
				args->precision = i;
				args->has_precision = 1;
			}
			else
				args->has_precision = 0;
			(*itr)++;
			return ;
		}
		args->precision = ft_atoi(itr);
	}
}

int		ft_getchar(char *itr, t_args *args)
{
	args->c = *itr;
	return (1);
}

char	*read_args(t_args *args, char *itr, va_list ap)
{
	long i;

	i = 0;
	while (*itr)
	{
		initialize_args(args);
		while (*itr == '-' || *itr == '0')
		{
			if (*itr == '-')
				args->flag_left = 1;
			else
				args->flag_zero = 1;
			itr++;
		}
		if (args->flag_left && args->flag_zero)
			args->flag_zero = 0;
		if (('0' < *itr && *itr <= '9') || *itr == '*')
			ft_getwidth(&itr, ap, args);
		if (*itr == '.')
			ft_getprec(&itr, ap, args, i);
		if (ft_strchr(CONV, *itr) || *itr == '%')
			return (itr + ft_getchar(itr, args));
		itr++;
	}
	return (itr);
}
