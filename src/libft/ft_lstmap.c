/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:03:09 by aboiarin          #+#    #+#             */
/*   Updated: 2023/11/13 13:30:13 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*e;
	void	*t;

	if (!lst || !f)
		return (0);
	new = 0;
	while (lst)
	{
		t = f(lst->content);
		e = ft_lstnew(t);
		if (!(e))
		{
			ft_lstclear(&new, del);
			free (t);
			return (0);
		}
		ft_lstadd_back(&new, e);
		lst = lst->next;
	}
	return (new);
}
