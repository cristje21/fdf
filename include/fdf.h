#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <MLX42.h>
# include "../libft/libft.h"

# define W 2050
# define H 1200
# define PAD 10

typedef struct s_matrix
{
	int				x;
	int				y;
	int				z;
	int				color;
	struct s_matrix	*next;
	struct s_matrix *down;
}					t_matrix;

typedef struct s_info
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_matrix	*matrix;		// input number matrix
	int			width;			// width of the matrix
	int			height;			// height of the matrix
	int			origin[2];		// central starting point
	int			unit_length;	// lenght of one unit of the matrix in pixels
	int			z_scaler;
}				t_info;

t_info		*parse_map(char *map);

void		put_line(int *start, int *end, int color, mlx_image_t *img);

int			get_width(t_matrix *tmp);
int			fdf_atoi(const char *str);

/*	utils	*/

int			ft_xtoi(char *hex);
void		add_back(t_matrix **head, t_matrix *to_add);
t_matrix	*new_node(int x, int y, int z, int color);

/*	key functions	*/

void	move_image(t_info *info, mlx_key_data_t key);
void	zoom_image(t_info *info, mlx_key_data_t key);
void	ft_listen_to_alicia_keys_baby(mlx_key_data_t key, void *info);

#endif