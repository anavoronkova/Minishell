/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 13:12:18 by aboiarin          #+#    #+#             */
/*   Updated: 2023/05/24 16:51:13 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	r;

	i = 0;
	if (n == 0)
		return (ft_strlen(src));
	while (*dest && i < n)
	{
		dest++;
		i++;
	}
	r = ft_strlcpy(dest, src, n - i);
	return (r + i);
}
