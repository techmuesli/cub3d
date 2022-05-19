/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:21:25 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/03/01 17:13:05 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include "libft.h"

# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 127
# endif

int		check_for_new_line(const char *string, int length);
char	**init_static(char **rest, int fd);
void	check_n_cleanup_static(char ***rest);

#endif
