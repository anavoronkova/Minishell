/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:53:58 by aboiarin          #+#    #+#             */
/*   Updated: 2023/11/18 16:08:38 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_arg(char type, va_list args)
{
	int	count;

	count = 0;
	if (type == '%')
		count += ft_print_char(type);
	else if (type == 'c')
		count += ft_print_char(va_arg(args, int));
	else if (type == 's')
		count += ft_print_str(va_arg(args, char *));
	else if (type == 'd' || type == 'i')
		count += ft_print_int(va_arg(args, int));
	else if (type == 'u')
		count += ft_print_uint(va_arg(args, unsigned int));
	else if (type == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), type);
	else if (type == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), type);
	else if (type == 'p')
		count += ft_print_ptr(va_arg(args, void *));
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += ft_print_arg(format[i + 1], args);
			i++;
		}
		else
			count += ft_print_c(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
