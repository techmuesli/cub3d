/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:31:21 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/08 11:49:51 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	*list_get(t_list *list)
{
	if (list->current == NULL)
		return (NULL);
	return (list->current->data);
}

void	*list_get_next(t_list *list)
{
	t_node	*node;

	node = list->current;
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
		return (NULL);
	list->current = node->next;
	return (node->next->data);
}

void	*list_get_prev(t_list *list)
{
	t_node	*node;

	node = list->current;
	if (node == NULL)
		return (NULL);
	if (node->prev == NULL)
		return (NULL);
	list->current = node->prev;
	return (node->prev->data);
}

void	*list_get_first(t_list *list)
{
	if (list->first == NULL)
		return (NULL);
	list->current = list->first;
	return (list->first->data);
}

void	*list_get_last(t_list *list)
{
	if (list->last == NULL)
		return (NULL);
	list->current = list->last;
	return (list->last->data);
}
