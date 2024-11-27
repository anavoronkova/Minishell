/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boiarinov <boiarinov@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:55:58 by aboiarin          #+#    #+#             */
/*   Updated: 2024/02/23 14:35:29 by boiarinov        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ext;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ext = ft_lstlast(*lst);
	ext->next = new;
}
