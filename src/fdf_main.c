/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/04 22:07:49 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>

void	print_matrix(int **matrix, int width)
{
	int i, j;

	i = 0;
	while (matrix[i])
	{
		j = 0;
		while (j < width)
		{
			ft_printf("%d ", matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	get_starting_position(t_info *info)
{
	info->central[x] = W >> 1;
	info->central[y] = H >> 1;
	if (info->width & 1)
		info->start[x] = info->central[x] - ((info->width >> 1) * info->unit_length);
	else
		info->start[x] = info->central[x] - (((info->width >> 1) - 1) * info->unit_length);
	if (info->height & 1)
		info->start[y] = info->central[y] - ((info->height >> 1) * info->unit_length);
	else
		info->start[y] = info->central[y] - (((info->height >> 1) - 1) * info->unit_length);
	if (!(info->width & 0))
		info->start[x] -= info->unit_length >> 1;
	if (!(info->height & 0))
		info->start[y] -= info->unit_length >> 1;
	ft_printf("central (%d)(%d)\n start (%d)(%d)\nunit size: %d\n", info->central[x], info->central[y], info->start[x], info->start[y], info->unit_length);
	//ft_printf("info->start[x]: %d\ninfo->start[y]: %d\nend x: %d, end y: %d\n", info->start[0], info->start[1], info->start[0] + (info->width * info->unit_length), info->start[1] + (info->height * info->unit_length));
	//exit(0);
}

void	get_unit_length(t_info *info)
{
	if (info->width > info->height)
	{
		info->unit_length = (W - PAD) / info->width;
		if (info->height * info->unit_length > (H - PAD))
			info->unit_length = (H - PAD) / info->height;
	}
	else
	{
		info->unit_length = (H - PAD) / info->height;
		if (info->width * info->unit_length > (W - PAD))
			info->unit_length = (W - PAD) / info->width;
	}
	get_starting_position(info);
}

void	put_dot(mlx_image_t *img, t_info *info)
{
	mlx_put_pixel(img, info->start[x], info->start[y], 0xFFFFFF);
	mlx_put_pixel(img, info->start[x] + 1, info->start[y], 0xFFFFFF);
	mlx_put_pixel(img, info->start[x] - 1, info->start[y], 0xFFFFFF);
	mlx_put_pixel(img, info->start[x], info->start[y] + 1, 0xFFFFFF);
	mlx_put_pixel(img, info->start[x], info->start[y] - 1, 0xFFFFFF);
}

int	main(void)
{
	t_info		*info;
	mlx_t		*mlx;
	mlx_image_t	*img;

	info = parse_map("test");
	get_unit_length(info);
	ft_printf("central x: %d, central y: %d\n", info->central[x], info->central[y]);
	ft_printf("start x: %d, start y: %d\nunit size: %d\n", info->start[x], info->start[y], info->unit_length);
	mlx = mlx_init(W, H, "bro", true);
	if (!mlx)
		ft_error("Error: malloc failure", errno);
	img = mlx_new_image(mlx, W, H);
	if (!img)
		ft_error("Error: malloc failure", errno);
	int i, j, s;
	i = 0;
	while (i < info->height)
	{
		j = 0;
		s = info->start[x];
		while (j < info->width)
		{
			put_dot(img, info);
			info->start[x] += info->unit_length;
			j++;
		}
		//ft_printf("end x: %d\n", info->start[x]);
		info->start[y] += info->unit_length;
		info->start[x] = s;
		i++;
	}
	mlx_image_to_window(mlx, img, PAD >> 1, PAD >> 1);
	mlx_loop(mlx);
	// exit(EXIT_SUCCESS);
}