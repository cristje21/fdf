/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/02 13:52:40 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>
#include <math.h>

void	get_unit_length(t_info *info)
{
	if (W <= H)
	{
		if (info->width > info->height)
			info->unit_length = ((W >> 1) - (PAD)) / info->width;
		else
			info->unit_length = ((W >> 1) - (PAD)) / info->height;
	}
	else
	{
		if (info->width > info->height)
			info->unit_length = ((H >> 1) - (PAD)) / info->width;
		else
			info->unit_length = ((H >> 1) - (PAD)) / info->height;
	}
	if (info->unit_length < 3)
		info->unit_length = 3;
	info->origin[0] = W >> 1;
	info->origin[1] = H >> 1;
}

void	print_everything(t_matrix *head)
{
	t_matrix	*tmp;

	tmp = head;
	while (head)
	{
		tmp = head;
		while (tmp)
		{
			ft_printf("x:%d, y:%d, z:%d, color:%d\n", tmp->x, tmp->y, tmp->z, tmp->color);
			tmp = tmp->next;
		}
		ft_printf("\n");
		head = head->down;
	}
}

void reassign_coords(t_info *info, t_matrix *matrix, int flag)
{
	matrix->x -= (info->width >> 1);
	matrix->y -= (info->height >> 1);
	if (matrix->next && flag)
		reassign_coords(info, matrix->next, 1);
	if (matrix->down)
		reassign_coords(info, matrix->down, 0);
}

static void iso_transformation(int *result, t_matrix *matrix, t_info *info)
{
	result[0] = ((matrix->x * info->unit_length) - (matrix->y * info->unit_length)) * cos(0.523599) + info->origin[0];
	result[1] = ((matrix->x * info->unit_length) + (matrix->y * info->unit_length)) * sin(0.523599) + info->origin[1] - matrix->z;
}

// bool	is_inscreen(int *start, int *end, int unit_length)
// {
// 	if (start[0] < -unit_length || start[0] < -unit_length)
// }

void	draw_all_lines(t_info *info, mlx_image_t *img, t_matrix *matrix, int flag)
{
	int	start[2];
	int	end[2];

	if (matrix == NULL)
		return ;
	if (matrix->next)
	{
		iso_transformation(start, matrix, info);
		iso_transformation(end, matrix->next, info);
		if (!is_inscreen(start, end, info->unit_length))
			put_line(start, end, matrix->color, img);
	}
	if (matrix->down)
	{
		iso_transformation(start, matrix, info);
		iso_transformation(end, matrix->down, info);
		put_line(start, end, matrix->color, img);
	}
	if (flag)
		draw_all_lines(info, img, matrix->next, 1);
	draw_all_lines(info, img, matrix->down, 0);
}

void	draw_full_screen(mlx_image_t *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char *argv[])
{
	t_info		*info;

	if (argc < 2)
		ft_error("no map supplied\n", -2);
	info = parse_map(argv[1]);
	get_unit_length(info);
	reassign_coords(info, info->matrix, 1);
	info->mlx = mlx_init(W, H, "bro", true);
	if (!info->mlx)
		ft_error("Error: malloc failure", errno);
	info->img = mlx_new_image(info->mlx, W, H);
	if (!info->img)
		ft_error("Error: malloc failure", errno);
	//print_everything(info->matrix);
	// exit(0);
	draw_full_screen(info->img, 0x000000FF);
	draw_all_lines(info, info->img, info->matrix, 1);
	mlx_image_to_window(info->mlx, info->img, 0, 0);
	mlx_key_hook(info->mlx, ft_listen_to_alicia_keys_baby, info);
	mlx_loop(info->mlx);
	exit(EXIT_SUCCESS);
}
