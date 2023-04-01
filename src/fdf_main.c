/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/03/30 20:29:41 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

#define WIDTH 10000
#define HEIGHT 5000

int	main(void)
{
	int start[] = {0, 0};
	int	end[] = {800, 1000};
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "bro", true);
	if (!mlx)
		return (-1);
	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	put_line(start, end, 0XFF0000FF, img);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}