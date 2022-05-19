/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_rm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:29:40 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/16 11:31:06 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

static int		list_resize(t_list *list);
static int		list_add_new_nodes(t_list *list, void **nodes);

/* rename to list_add_back ? !!!!! */
void	*list_add(t_list *list, void *data)
{
	t_node	*node;

	if (list->total == list->capacity)
	{
		if (list_resize(list) != 0)
			return (NULL);
	}
	node = stack_pop(list->free_nodes);
	if (node == NULL)
		return (NULL);
	if (list->total == 0)
		list->first = node;
	if (list->data_size == 0)
		node->data = data;
	else
		ft_memcpy(node->data, data, list->data_size);
	if (list->last != NULL)
		list->last->next = node;
	else
		node->next = NULL;
	node->prev = list->last;
	list->total++;
	list->current = node;
	list->last = node;
	return (node);
}

//void	*list_add_before(t_list *list, void *data);

/* if possible -> change to list_add_before */
void	*list_add_front(t_list *list, void *data)
{
	t_node	*node;

	if (list->total == list->capacity)
	{
		if (list_resize(list) != 0)
			return (NULL);
	}
	node = stack_pop(list->free_nodes);
	if (node == NULL)
		return (NULL);
	node->next = list->first;
	if (list->first != NULL)
		list->first->prev = node;
	list->first = node;
	if (list->data_size == 0)
		node->data = data;
	else
		ft_memcpy(node->data, data, list->data_size);
	node->prev = NULL;
	list->total++;
	list->current = node;
	if (list->total == 1)
		list->last = node;
	return (node);
}

static int	list_resize(t_list *list)
{
	size_t	index;
	size_t	new_capacity;
	void	**new;

	new_capacity = list->capacity + list->grow_count;
	new = malloc(new_capacity * sizeof(void *));
	if (new == NULL)
		return (1);
	index = 0;
	while (index < list->capacity)
	{
		new[index] = list->nodes[index];
		index++;
	}
	if (list_add_new_nodes(list, new) != 0)
	{
		free(new);
		return (1);
	}
	free(list->nodes);
	list->nodes = new;
	list->capacity = new_capacity;
	return (0);
}

/* possbile optimization for while() */
static int	list_add_new_nodes(t_list *list, void **nodes)
{
	char	*buf;
	size_t	index;
	size_t	pos;
	t_node	*node;

	buf = ft_calloc(list->grow_count, sizeof(t_node) + list->data_size);
	if (buf == NULL)
		return (1);
	vector_add(list->data_allocs, buf);
	pos = 0;
	index = list->capacity;
	while (index < list->capacity + list->grow_count)
	{
		nodes[index] = &buf[pos * (sizeof(t_node) + list->data_size)];
		if (list->data_size != 0)
		{
			node = nodes[index];
			node->data = &buf[pos * (sizeof(t_node) + list->data_size)]
				+ sizeof(t_node);
		}
		stack_push(list->free_nodes, nodes[index]);
		pos++;
		index++;
	}
	return (0);
}

/* !!!!! discuss how current should be handled on delete */
void	list_delete(t_list *list)
{
	t_node	*node;

	if (list->current == NULL)
		return ;
	node = list->current;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (list->total == 1)
		list->first = NULL;
	if (list->first == node)
		list->first = node->next;
	if (list->last == node)
		list->last = node->prev;
	list->current = node->next;
	if (list->cleanup_cb != NULL)
		list->cleanup_cb(node->data);
	if (node->data != NULL && list->data_size == 0)
		free(node->data);
	list->total--;
	node->next = NULL;
	node->prev = NULL;
	stack_push(list->free_nodes, node);
}
