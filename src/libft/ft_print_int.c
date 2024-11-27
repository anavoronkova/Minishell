/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:40:22 by aboiarin          #+#    #+#             */
/*   Updated: 2023/10/24 16:16:48 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_int(long n)
{
	char	*nbstr;
	int		count;

	count = 0;
	nbstr = ft_itoa(n);
	if (!nbstr)
		return (0);
	count += ft_print_str(nbstr);
	free(nbstr);
	return (count);
}
