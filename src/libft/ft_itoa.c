/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:12:27 by aboiarin          #+#    #+#             */
/*   Updated: 2023/10/24 15:35:59 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr_local(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_putnbr_local(n / 10, str, i);
		ft_putnbr_local(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*r;
	int		i;
	long	nbr;

	nbr = n;
	r = (char *)malloc(sizeof(char) * (ft_nbrlen(nbr) + 1));
	if (r == 0)
		return (0);
	i = 0;
	if (nbr < 0)
	{
		r[i++] = '-';
		nbr *= -1;
	}
	ft_putnbr_local(nbr, r, &i);
	r[i] = '\0';
	return (r);
}
