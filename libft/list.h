/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 16:23:52 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/02/15 13:34:27 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include "stack.h"
# include "vector.h"

typedef void	(*t_cleanup_cb)(void *data);

typedef struct s_node
{
	void			*data;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct s_list
{
	size_t			capacity;
	size_t			data_size;
	size_t			grow_count;
	size_t			total;
	t_cleanup_cb	cleanup_cb;
	t_node			*current;
	t_node			*first;
	t_node			*last;
	t_stack			*free_nodes;
	t_vector		*data_allocs;
	void			**nodes;
}				t_list;

t_list	*list_init(size_t capacity, size_t grow_count, size_t size);
void	list_cleanup(t_list *list);
void	list_custom_cleanup(t_list *list, void (*cleanup_cb)(void *data));
void	*list_add(t_list *list, void *data);
void	*list_add_front(t_list *list, void *data);
//void	*list_add_before(t_list *list, void *data);
void	list_delete(t_list *list);
void	*list_get(t_list *list);
void	*list_get_next(t_list *list);
void	*list_get_prev(t_list *list);
void	*list_get_first(t_list *list);
void	*list_get_last(t_list *list);
size_t	list_get_total_number(t_list *list);

#endif
