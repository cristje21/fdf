/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 21:42:15 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/01 22:11:33 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	move_image(t_info *info, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->origin[0] += 7;
	if (key.key == MLX_KEY_DOWN && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->origin[1] += 7;
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->origin[0] -= 7;
	if (key.key == MLX_KEY_UP && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->origin[1] -= 7;
	draw_full_screen(info->img, 0x000000FF);
	draw_all_lines(info, info->img, info->matrix, 1);
	mlx_image_to_window(info->mlx, info->img, 0, 0);
}

void	zoom_image(t_info *info, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_KP_ADD && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->unit_length += 4;
	if (key.key == MLX_KEY_KP_SUBTRACT && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		info->unit_length -= 4;
	if (info->unit_length < 3)
		info->unit_length = 3;
	draw_full_screen(info->img, 0x000000FF);
	draw_all_lines(info, info->img, info->matrix, 1);
	mlx_image_to_window(info->mlx, info->img, 0, 0);
}

void	scale_z(t_info *info, mlx_key_data_t key)
{
	if (key.modifier == 0)
	{
		// increase
		
	}
	else
	{

	}
}

void	ft_listen_to_alicia_keys_baby(mlx_key_data_t key, void *info)
{
	if (key.key >= MLX_KEY_RIGHT && key.key <= MLX_KEY_UP)
		move_image(info, key);
	if (key.key == MLX_KEY_KP_ADD || key.key == MLX_KEY_KP_SUBTRACT)
		zoom_image(info, key);
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(((t_info *)info)->mlx);
	if (key.key == MLX_KEY_Z)
		scale_z(info, key);
}
