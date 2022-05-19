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

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_map
{
	char	*texture_north;
	char	*texture_east;
	char	*texture_south;
	char	*texture_west;
	int		**data;
	int		x;
	int		y;
	t_color	ceiling;
	t_color	floor;
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
	t_vec		direction;
	t_vec		camera_plane;
	void		*mlx;
	void		*window;
	uint64_t	last_time;
	uint64_t	current_time;
}				t_data;

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef enum e_info_type
{
	INFO_TYPE_NO = 0,
	INFO_TYPE_EA,
	INFO_TYPE_SO,
	INFO_TYPE_WE,
	INFO_TYPE_FLOOR,
	INFO_TYPE_CEILING,
	INFO_TYPE_UNKNOWN,
}				t_info_type;

// init.c
t_data		*fdf_init(int width, int height, char *title);

// cleanup.c
void		fdf_cleanup(t_data **data);

// input.c
int			read_input_file(t_data *data, char *filename);

// input_check.c
int			check_input(t_data *data);

// input_info.c
int			get_type_identifier(char *input);

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

#endif
