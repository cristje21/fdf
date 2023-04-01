/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/03/28 22:18:14 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <MLX42.h>

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

//Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

int	main()
{
	int x1 = 30, x2 = 50, y1 = 10, y2 = 18;
	int m_new = 2 * (y2 - y1); // 6
	int se = m_new - (x2 - x1);

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_t* mlx = mlx_init(1000, 500, "line", true);
	if (!mlx)
		return (0);
	mlx_image_t* img = mlx_new_image(mlx, 1000, 500);
	printf("se: %d\n", se);
	int y = y1;
	int x = x1;
	while (x <= x2)
	{
		mlx_put_pixel(img, x, y, 0x03E936);
		printf("x(%d),y(%d)\t", x, y);
		se += m_new; // + 6
		printf("se: %d\n", se);
		if (se >= 0)
		{
			y++;
			se -= 2 * (x2 - x1);
			printf("se after y inc: %d\n", se);
		}
		x++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}