#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <MLX42.h>
# include "../libft/libft.h"

# define W 200
# define H 200
# define PAD 4

# define x 0
# define y 1

typedef struct s_matrix
{
	int				*line;
	struct s_matrix	*next;
}					t_lines;

typedef struct s_info
{
	int				**matrix;		// input number matrix
	int				width;			// width of the matrix
	int				height;			// height of the matrix
	int				central[2];		// central starting point
	int				start[2];		// to start drawing
	int				unit_length;	// lenght of one unit of the matrix in pixels
}					t_info;

t_info	*parse_map(char *map);

void	put_line(int *start, int *end, int color, mlx_image_t *img);

int		get_width(char *s);
int		fdf_atoi(const char *str);
//	210		26
//	1790	974
#endif