/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:49:35 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/11/08 16:04:44 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_c_vector(char **vector)
{
	int	i;

	if (vector == NULL)
		return ;
	i = 0;
	while (vector[i] != NULL)
	{
		free(vector[i]);
		i++;
	}
	free(vector);
}

void	cub3d_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dest = color;
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (milliseconds);
}

void	ft_bzero64(void *s, size_t n)
{
	uint64_t	*data;

	if (n == 0)
		return ;
	if (n % sizeof(uint64_t) != 0)
		return ;
	data = s;
	n /= sizeof(uint64_t);
	while (n > 0)
	{
		*data = 0;
		data++;
		n--;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
