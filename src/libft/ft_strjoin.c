/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avoronko <avoronko@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:11:57 by aboiarin          #+#    #+#             */
/*   Updated: 2024/03/09 14:48:47 by avoronko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*r;
	unsigned int	i;
	unsigned int	l;

	i = 0;
	l = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	r = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (r == 0)
		return (0);
	while (s1[l])
	{
		r[i] = s1[l];
		i++;
		l++;
	}
	l = 0;
	while (s2[l])
	{
		r[i + l] = s2[l];
		l++;
	}
	r[i + l] = '\0';
	return (r);
}
