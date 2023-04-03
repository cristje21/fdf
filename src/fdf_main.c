/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/03 21:51:42 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

#define WIDTH 10000
#define HEIGHT 5000

int	main(void)
{
	int	**matrix;
	int	width;
	int	i, j;

	matrix = NULL;
	width = parse_map(&matrix, "test");
	j = 0;
	while (matrix[j])
	{
		i = 0;
		while (i < width)
		{
			ft_printf("%d, ", matrix[j][i]);
			i++;
		}
		ft_printf(" <---\n");
		j++;
	}
	// int start[] = {0, 0};
	// int	end[] = {800, 1000};
	// mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "bro", true);
	// if (!mlx)
	// 	return (-1);
	// mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// put_line(start, end, 0XFF0000FF, img);
	// mlx_image_to_window(mlx, img, 0, 0);
	// mlx_loop(mlx);
	exit(EXIT_SUCCESS);
}