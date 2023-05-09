/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_main.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 16:46:48 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/09 14:45:03 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdio.h>
#include <math.h>

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

static void iso_transformation(int *result, t_matrix *matrix, t_info *info)
{
	result[0] = ((matrix->x * info->unit_length) - (matrix->y * info->unit_length)) * cos(0.523599) + info->origin[0];
	result[1] = ((matrix->x * info->unit_length) + (matrix->y * info->unit_length)) * sin(0.523599) + info->origin[1] - (matrix->z * info->z_scaler);
}

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
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

void	change_bg(t_info *info, int key)
{
	if (key == MLX_KEY_KP_0) // teal green
		info->bg_color = get_rgba(57, 179, 149, 255);
	if (key == MLX_KEY_KP_1) // sky blue
		info->bg_color = get_rgba(153, 228, 255, 255);
	if (key == MLX_KEY_KP_2) // sunset
		info->bg_color = get_rgba(255, 66, 0, 191);
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
}

void	single_events(mlx_key_data_t key, void *info)
{
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(((t_info *)info)->mlx);
	if (key.key == MLX_KEY_C && key.action == MLX_PRESS)
		recentre(info);
	if (key.modifier == MLX_SHIFT && key.key >= MLX_KEY_KP_0 && key.key <= MLX_KEY_KP_9)
		change_bg(info, key.key);
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
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
	mlx_image_to_window(info->mlx, info->img, 0, 0);
	mlx_key_hook(info->mlx, single_events, info);
	mlx_loop_hook(info->mlx, ft_listen_to_alicia_keys_baby, info);
	mlx_loop(info->mlx);
	exit(EXIT_SUCCESS);
}
