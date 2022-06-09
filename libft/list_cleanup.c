/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:07:23 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/06/09 13:51:54 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "vector.h"

/* callback should free everything, but the data pointer itself
!!!!! stack_cleanup() is not called !!!!! check to call it
!!!!! CUSTOM CLEANUP is not called for preallocated memory
-> BUT SHOULD BE CALLED*/
void	list_custom_cleanup(t_list *list, void (*cleanup_cb)(void *data))
{
	list->cleanup_cb = cleanup_cb;
}

void	list_cleanup(t_list *list)
{
	t_node	*node;

	if (list == NULL)
		return ;
	node = list->first;
	while (node != NULL)
	{
		if (list->cleanup_cb != NULL)
			list->cleanup_cb(node->data);
		if (node->data != NULL && list->data_size == 0)
			free(node->data);
		node = node->next;
	}
	vector_cleanup(list->data_allocs);
	free(list->nodes);
	free(list->free_nodes->nodes);
	free(list->free_nodes);
	free(list);
	return ;
}
