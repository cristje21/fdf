#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <MLX42.h>
# include "../libft/libft.h"

typedef struct s_matrix
{
	int				*line;
	struct s_matrix	*next;
}					s_lines;

void	put_line(int *start, int *end, int color, mlx_image_t *img);
int		parse_map(int ***result, char *map);
int		fdf_atoi(const char *str);
int		get_width(char *s);

#endif