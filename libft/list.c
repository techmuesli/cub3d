/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:11:38 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/16 11:23:08 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"
#include "list.h"
#include "stack.h"

static void		**list_init_nodes(t_list *list, size_t count, size_t size);
static void		set_up_nodes(void **nodes, char *buf, size_t count,
					size_t size);
static t_stack	*list_init_stack(void **nodes, size_t count);

t_list	*list_init(size_t capacity, size_t grow_count, size_t size)
{
	t_list	*list;

	if (capacity == 0)
		return (NULL);
	list = ft_calloc(1, sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->nodes = list_init_nodes(list, capacity, size);
	if (list->nodes == NULL)
	{
		free(list);
		return (NULL);
	}
	list->free_nodes = list_init_stack(list->nodes, capacity);
	if (list->free_nodes == NULL)
	{
		vector_cleanup(list->data_allocs);
		free(list->nodes);
		free(list);
		return (NULL);
	}
	list->capacity = capacity;
	list->grow_count = grow_count;
	list->data_size = size;
	return (list);
}

static void	**list_init_nodes(t_list *list, size_t count, size_t size)
{
	char	*buf;
	void	**nodes;

	list->data_allocs = vector_init(10, 10, 0);
	if (list->data_allocs == NULL)
		return (NULL);
	nodes = malloc(count * sizeof(void *));
	if (nodes == NULL)
	{
		vector_cleanup(list->data_allocs);
		return (NULL);
	}
	buf = ft_calloc(count, sizeof(t_node) + size);
	if (buf == NULL)
	{
		vector_cleanup(list->data_allocs);
		free(nodes);
		return (NULL);
	}
	vector_add(list->data_allocs, buf);
	set_up_nodes(nodes, buf, count, size);
	return (nodes);
}

static void	set_up_nodes(void **nodes, char *buf, size_t count, size_t size)
{
	size_t	index;
	t_node	*node;

	index = 0;
	while (index < count)
	{
		nodes[index] = &buf[index * (sizeof(t_node) + size)];
		if (size != 0)
		{
			node = nodes[index];
			node->data = &buf[index * (sizeof(t_node) + size)]
				+ sizeof(t_node);
		}
		index++;
	}
}

static t_stack	*list_init_stack(void **nodes, size_t count)
{
	size_t	index;
	t_stack	*stack;

	stack = stack_init(count);
	if (stack == NULL)
		return (NULL);
	index = count - 1;
	while (index > 0)
	{
		stack_push(stack, nodes[index]);
		index--;
	}
	stack_push(stack, nodes[index]);
	return (stack);
}
