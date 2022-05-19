/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:10:39 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/05 18:37:17 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "stack.h"

static int	stack_resize(t_stack *stack);

t_stack	*stack_init(size_t capacity)
{
	t_stack	*stack;

	stack = ft_calloc(1, sizeof(t_stack));
	if (stack == NULL)
		return (NULL);
	stack->nodes = ft_calloc(capacity, sizeof(void *));
	if (stack->nodes == NULL)
	{
		free(stack);
		return (NULL);
	}
	stack->capacity = capacity;
	return (stack);
}

void	stack_cleanup(t_stack *stack)
{
	size_t	index;
	void	*node;

	if (stack == NULL)
		return ;
	index = 0;
	while (index < stack->total)
	{
		node = stack_pop(stack);
		if (node != NULL)
			free(node);
		index++;
	}
	free(stack->nodes);
	free(stack);
}

/*void	stack_custom_cleanup(t_stack *stack);*/
/*void	stack_clear(t_stack *stack);*/

void	*stack_push(t_stack *stack, void *node)
{
	size_t	index;

	index = stack->total;
	if (index == stack->capacity)
	{
		if (stack_resize(stack) != 0)
			return (NULL);
	}
	stack->nodes[index] = node;
	stack->total++;
	return (stack->nodes[index]);
}

static int	stack_resize(t_stack *stack)
{
	size_t	index;
	size_t	new_capacity;
	void	**new;

	new_capacity = stack->capacity * 2;
	new = malloc(new_capacity * sizeof(void *));
	if (new == NULL)
		return (1);
	index = 0;
	while (index < stack->total)
	{
		new[index] = stack->nodes[index];
		index++;
	}
	free(stack->nodes);
	stack->nodes = new;
	stack->capacity = new_capacity;
	return (0);
}

void	*stack_pop(t_stack *stack)
{
	if (stack->total == 0)
		return (NULL);
	stack->total--;
	return (stack->nodes[stack->total]);
}
