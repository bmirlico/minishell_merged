/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 21:16:24 by bmirlico          #+#    #+#             */
/*   Updated: 2023/05/17 18:15:59 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*new_elem;

	if (!lst || !f || !del)
		return (NULL);
	lst_new = 0;
	while (lst != NULL)
	{
		new_elem = ft_lstnew((*f)(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&lst_new, (*del));
			return (0);
		}
		ft_lstadd_back(&lst_new, new_elem);
		lst = lst->next;
	}
	return (lst_new);
}
