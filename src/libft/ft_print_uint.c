/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:42:11 by aboiarin          #+#    #+#             */
/*   Updated: 2023/10/24 16:16:48 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_unint_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*ft_utoa(unsigned int n)
{
	char	*nbstr;
	int		len;

	len = ft_unint_len(n);
	nbstr = ft_calloc(len + 1, sizeof(char));
	if (!nbstr)
		return (0);
	while (n != 0)
	{
		nbstr[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (nbstr);
}

int	ft_print_uint(unsigned int n)
{
	char	*nbstr;
	int		count;

	count = 0;
	if (n == 0)
		count += ft_print_c('0');
	nbstr = ft_utoa(n);
	if (!nbstr)
		return (0);
	count += ft_print_str(nbstr);
	free(nbstr);
	return (count);
}
