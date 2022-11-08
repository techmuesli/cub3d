//
// create_map_files.c
//

#include "../include/cub3d.h"

const char	*level1 = "NO ./textures/xpms/red_bricks.xpm\n\
SO ./textures/xpms/red_bricks.xpm\n\
WE ./textures/xpms/red_bricks.xpm\n\
EA ./textures/xpms/red_bricks.xpm\n\
F 150,150,150\n\
C 204,204,255\n\
\n\
        1111111211111121111112111\n\
        1000000000110000000000001\n\
        1011000001110000001000001\n\
        1001000000D00000001000001\n\
112111111011000001110000001000001\n\
P0000000001100000111D121111112111\n\
11210111111111011100000010001\n\
11110111112121011101010010002\n\
110000001101010111000000D0001\n\
1000000000000000D000000010001\n\
10000000000000001101010010001\n\
11000001110101011111011120N0211\n\
11110111 1110101 101111010001\n\
11112111 1112121 111111111111";

const char	*level2 = "NO ./textures/xpms/blue_bricks.xpm\n\
SO ./textures/xpms/blue_bricks.xpm\n\
WE ./textures/xpms/blue_bricks.xpm\n\
EA ./textures/xpms/blue_bricks.xpm\n\
\n\
F 214,168,41\n\
C 133,122,91\n\
\n\
11111111121P12111111111\n\
10000000200000200000001\n\
10111110102220101111101\n\
10100010102220101000101\n\
10101010000000001010101\n\
10101011111D11111010101\n\
10101000000000000010101\n\
10101111110101111110101\n\
10001 10000100001 10001\n\
11111110111111101111111\n\
10001000D00000D00010001\n\
10001012100N00121010001\n\
10000010D00000D01000001\n\
11111110111111101111111\n\
10001 10000100001 10001\n\
10101111110101111110101\n\
10101000000000000010101\n\
10101011111D11111010101\n\
10101010000000001010101\n\
10100010102220101000101\n\
10111110102220101111101\n\
10000000200000200000001\n\
11111111121P12111111111";

const char	*level3 = "NO ./textures/xpms/grey_bricks_light.xpm\n\
SO ./textures/xpms/grey_bricks_light.xpm\n\
EA ./textures/xpms/grey_bricks_light.xpm\n\
WE ./textures/xpms/grey_bricks_light.xpm\n\
\n\
F 255,255,255\n\
C 0,0,0\n\
\n\
11111111111111111\n\
1000000000W100001\n\
10110111111101101\n\
10100000100000101\n\
10111111111110111\n\
10000000000000101\n\
10111110111111101\n\
10100010100000001\n\
10101010101111101\n\
11101010100000101\n\
10101110111110101\n\
10100000001000101\n\
10110111111110101\n\
10000000000000101\n\
111111111111111X1";

static char	*create_filename(char *filename);

char *create_map_file(int level)
{
	char	*map;
	int			fd;

	map = create_filename("temp");
	if (map == NULL)
		return (NULL);
	fd = open(map,  O_RDWR | O_CREAT, 0666);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	if (level == 1)
		write(fd, level1, ft_strlen(level1));
	else if (level == 2)
		write(fd, level2, ft_strlen(level2));
	else if (level == 3)
		write(fd, level3, ft_strlen(level3));
	else
	{
		free(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}

static char	*create_filename(char *filename)
{
	int	i;

	filename = ft_strjoin("./", filename);
	i = ft_strlen(filename) - 1;
	while (access(filename, F_OK) == 0)
	{
		if (filename[i] == 'z' || filename[i] == 'Z')
			i--;
		if (i == 0)
		{
			free(filename);
			return (NULL);
		}
		filename[i]++;
	}
	i = 0;
	return (filename);
}
