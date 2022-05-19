/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:13:43 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/02 15:47:04 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <stdlib.h>

typedef struct s_stack
{
	size_t	capacity;
	size_t	total;
	void	**nodes;
}				t_stack;

t_stack	*stack_init(size_t capacity);
void	stack_cleanup(t_stack *stack);
/*void	stack_custom_cleanup(t_stack *stack);*/
/*void	stack_clear(t_stack *stack);*/
void	*stack_push(t_stack *stack, void *node);
void	*stack_pop(t_stack *stack);

#endif
