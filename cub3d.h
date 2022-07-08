/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandtn <dbrandtn@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:47:07 by dbrandtn          #+#    #+#             */
/*   Updated: 2022/07/08 11:23:27 by dbrandtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdio.h>
// !!!!! check for printfs -> change to ft_printf

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "libft/vector.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

# define TEX_WIDTH 256
# define TEX_HEIGHT 256

# define START_WIDTH 1000
# define START_HEIGHT 600
# define SPRITE_COUNT 5

# define LEVEL_1 "./maps/level1.cub"
# define LEVEL_2 "./maps/level2.cub"
# define LEVEL_3 "./maps/level3.cub"
# define BONUS_LEVEL "./maps/bonus_level.cub"

# define PORT 4242
# define BUFSIZE 8192
# define MAX_LEN 32

typedef enum e_info_type
{
	INFO_TYPE_NO = 0,
	INFO_TYPE_EA,
	INFO_TYPE_SO,
	INFO_TYPE_WE,
	INFO_TYPE_FLOOR,
	INFO_TYPE_CEILING,
	INFO_TYPE_EMPTY,
	INFO_TYPE_MAP,
}				t_info_type;

typedef enum e_map_type
{
	MAP_TYPE_UNKNOWN = -2,
	MAP_TYPE_NOTHINGNESS = -1,
	MAP_TYPE_EMPTY_SPACE = 0,
	MAP_TYPE_WALL,
	MAP_TYPE_WALL_SPRITE,
	MAP_TYPE_PORTAL,
	MAP_TYPE_EXIT,
	MAP_TYPE_DOOR,
	MAP_TYPE_N,
	MAP_TYPE_E,
	MAP_TYPE_S,
	MAP_TYPE_W,
	MAP_END_OF_LINE,
}				t_map_type;

typedef struct s_network
{
	struct sockaddr_in	server;
	int					socket;
}				t_network;

typedef struct s_client_data
{
	uint64_t	time;
	char		user_name[MAX_LEN];
}				t_client_data;

typedef struct s_server_data
{
	int				num_of_games;
	int				rank;
	t_client_data	top[10];
}				t_server_data;

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

typedef struct s_map_info
{
	int			open_door;
	int			visible;
	int			frame_num;
	uint64_t	sprite_time;
}				t_map_info;

typedef struct s_map
{
	char		*tx_no;
	char		*tx_ea;
	char		*tx_so;
	char		*tx_we;
	int			**data;
	t_map_info	**info;
	int			x;
	int			y;
	t_color		ceiling;
	t_color		flr;
}				t_map;

typedef struct s_image
{
	char	*addr;
	int		bpp;
	int		endian;
	int		size_line;
	void	*img;
}				t_image;

typedef struct s_minimap
{
	t_image	img;
	int		width;
	int		height;
}				t_minimap;

typedef struct s_rect
{
	int	width;
	int	height;
	int	x0;
	int	y0;
	int	color;
}				t_rect;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}			t_texture;

typedef struct s_start
{
	t_texture	start;
	uint64_t	start_time;
	int			start_flag;
}				t_start;

typedef struct s_rc
{
	t_vec	ray_dir;
	t_vec	delta_dist;
	t_vec	side_dist;
	t_vec_i	px;
	t_vec_i	map;
	t_vec_i	step;
	t_vec_i	tex;
	int		side;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		color;
	int		hit;
	double	tex_step;
	double	tex_pos;
}		t_rc;

typedef struct s_data
{
	char		*level;
	char		*user_name;
	t_image		image;
	t_minimap	minimap;
	t_map		map;
	t_start		start;
	t_texture	tx_no;
	t_texture	tx_so;
	t_texture	tx_we;
	t_texture	tx_ea;
	t_texture	tx_door;
	t_texture	tx_exit;
	t_texture	tx_torch[SPRITE_COUNT];
	t_texture	tx_portal[SPRITE_COUNT];
	t_vec		pos;
	t_vec		dir;
	t_vec		camera_plane;
	t_vec_i		mouse_pos;
	void		*mlx;
	void		*window;
	uint64_t	initial_time;
	uint64_t	current_time;
	uint64_t	last_time;
	uint64_t	frame_time;
	double		move_speed;
	double		rot_speed;
	int			new_level;
	int			exit;
	int			frames;
	int			start_timer;
}				t_data;

// init.c
t_data		*cub3d_init(int width, int height, char *title, char *user_name);

// cleanup.c
void		cub3d_cleanup(t_data **data);
void		free_map(t_data *data);

// input.c
int			read_input_file(t_data *data, char *filename);
int			get_map_width(int *line);

// input_check.c
int			check_input(t_data *data);

// input_info.c
int			get_type_identifier(char *input);
int			get_type_info(t_map *map, char *input, int type);

// input_map.c
int			load_map(t_data *data, char *line, int fd);

// hooks.c
void		set_up_hooks(void *window, t_data *data);
int			end_loop(void *param);

// run.c
int			run_loop(void *param);

// utils.c
void		free_c_vector(char **vector);
void		cub3d_mlx_pixel_put(t_image *img, int x, int y, int color);
long long	get_time(void);
void		ft_bzero64(void *s, size_t n);
int			create_trgb(int t, int r, int g, int b);

// minimap.c
int			return_color(t_data *data, int flag);
void		update_map(t_data *data);
void		render_minimap(t_data *data);

// minimap_utils.c
void		select_square_color(t_data *data, t_vec_i map, t_vec_i pix_pos);
int			render_rect(t_image *img, t_rect rect);
t_vec_i		calc_square(t_data *data);
void		render_time(t_data *data);

// raycast.c
int			raycast(t_data *data);

// raycast_utils.c
void		calc_wall_color(t_data *data, t_rc *rc);
void		calc_move_speeds(t_data *data);
void		check_open_door(t_data *data, t_rc *rc);
void		finish_game(t_data *data);

// keys.c
void		key_w(t_data *data);
void		key_a(t_data *data);
void		key_s(t_data *data);
void		key_d(t_data *data);
void		key_f(t_data *data);

// rotate.c
void		key_left(t_data *data);
void		key_right(t_data *data);
void		check_door(t_data *data, int x, int y);

// textures.c
int			parse_textures(t_data *data);

// startscreen.c
void		render_startscreen(t_data *data);

// network.c
t_network	*network_init(char *domain_name);
void		network_cleanup(t_network *network);
int			connect_to_server(t_network *network);
//int			send_data(t_network *network, char *data, size_t size);
int			recv_data(t_data *data, t_network *network, t_client_data *client);

// result.c
void		server_fetch(t_data *data);
void		render_scoreboard(t_data *data, t_server_data *server,
				t_client_data *client);

#endif
