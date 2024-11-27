/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:12:31 by aboiarin          #+#    #+#             */
/*   Updated: 2024/03/25 17:21:51 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	l;
	int		r;

	l = 0;
	if (n == 0)
		return (0);
	while (s1[l] && s2[l] && s1[l] == s2[l]
		&& l < (n - 1))
		l++;
	r = (unsigned char)s1[l] - (unsigned char)s2[l];
	return (r);
}
