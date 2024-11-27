/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:02:07 by aboiarin          #+#    #+#             */
/*   Updated: 2023/11/13 13:30:13 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ext;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		ext = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ext;
	}
	*lst = 0;
}
