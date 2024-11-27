/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:59:49 by aboiarin          #+#    #+#             */
/*   Updated: 2023/11/18 15:59:54 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_node_len(unsigned long n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	ft_print_pbody(unsigned long n)
{
	if (n >= 16)
	{
		ft_print_pbody(n / 16);
		ft_print_pbody(n % 16);
	}
	else
	{
		if (n < 10)
			ft_print_c(n + '0');
		else
			ft_print_c((n - 10) + 'a');
	}
}

int	ft_print_ptr(void *node)
{
	int				count;
	unsigned long	p;

	count = 0;
	if (node == 0)
		return (ft_print_str("(nil)"));
	p = (unsigned long)node;
	count += write(1, "0x", 2);
	ft_print_pbody(p);
	count += ft_node_len(p);
	return (count);
}
