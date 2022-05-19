// !!!!!

#ifndef CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "libft/vector.h"

# include <stdio.h> // !!!!!

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_vec_i
{
	int	x;
	int	y;
}				t_vec_i;

typedef struct s_map
{
	int	**data;
	int	x;
	int	y;
}				t_map;

typedef struct s_image
{
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		size_line;
	void	*img;
}				t_image;

typedef struct s_data
{
	t_image		image;
	t_map		map;
	t_vec		pos;
	t_vec		dir;
	t_vec		camera_plane;
	void		*mlx;
	void		*window;
	uint64_t	current_time;
	uint64_t	last_time;
	uint64_t	frame_time;
	double		move_speed;
	double		rot_speed;
}				t_data;

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

// init.c
t_data		*fdf_init(int width, int height, char *title);

// cleanup.c
void		fdf_cleanup(t_data **data);

// input.c
int			read_input_file(t_data *data, char *filename);

// hooks.c
void		set_up_hooks(void *window, t_data *data);

// run.c
int			run_loop(void *param);

// utils.c
void		free_c_vector(char **vector);
void		cub3d_mlx_pixel_put(t_image *img, int x, int y, int color);
long long	get_time(void);
void		ft_bzero64(void *s, size_t n);

// raycast.c
int			raycast(t_data *data);

// keys.c
void		key_w(t_data *data);
void		key_a(t_data *data);
void		key_s(t_data *data);
void		key_d(t_data *data);

void		key_left(t_data *data);
void		key_right(t_data *data);

#endif
