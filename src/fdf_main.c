/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/03/22 22:34:00 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <MLX42.h>

#define WIDTH 500
#define HEIGHT 500

int	main(int argc, char *argv[])
{
	mlx_t *mlx;

	if (argc != 5)
		exit (0);
	mlx = mlx_init(WIDTH, HEIGHT, "leggo\n\n", false);
	if (!mlx)
		exit(1);
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		exit(1);
	// use 
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
}