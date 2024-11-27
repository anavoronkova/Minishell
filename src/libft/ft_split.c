/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:12:18 by aboiarin          #+#    #+#             */
/*   Updated: 2024/04/07 19:08:19 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_local(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			++i;
			while (*str && *str != c)
				++str;
		}
		else
			++str;
	}
	return (i);
}

static void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**ft_real_split(char **arr, char const *s, char c)
{
	int		i;
	int		l;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			l = 0;
			while (*s && *s != c && ++l)
				++s;
			arr[i++] = ft_substr(s - l, 0, l);
			if (arr[i - 1] == 0)
			{
				ft_free_arr(arr);
				return (0);
			}
		}
		else
			++s;
	}
	arr[i] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (ft_strlen_local(s, c) + 1));
	if (!arr)
		return (0);
	arr = ft_real_split(arr, s, c);
	return (arr);
}
