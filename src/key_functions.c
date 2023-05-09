/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 21:42:15 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/09 12:55:06 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <string.h>

void	move_image(t_info *info, int key)
{
	if (key == MLX_KEY_RIGHT)
		info->origin[0] += 10;
	if (key == MLX_KEY_DOWN)
		info->origin[1] += 10;
	if (key == MLX_KEY_LEFT)
		info->origin[0] -= 10;
	if (key == MLX_KEY_UP)
		info->origin[1] -= 10;
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
}

void	zoom_image(t_info *info, int key)
{
	if (key == MLX_KEY_KP_ADD)
		info->unit_length += 4;
	if (key == MLX_KEY_KP_SUBTRACT)
		info->unit_length -= 4;
	if (info->unit_length < 3)
		info->unit_length = 3;
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
}

void	scale_z(t_info *info, int key)
{
	if (key == MLX_KEY_X)
		info->z_scaler++;
	else
		info->z_scaler--;
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
}

void	recentre(t_info *info)
{
	get_unit_length(info);
	draw_full_screen(info->img, info->bg_color);
	draw_all_lines(info, info->img, info->matrix, 1);
}

void	translate(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
		move_image(info, MLX_KEY_RIGHT);
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
		move_image(info, MLX_KEY_LEFT);
	if (mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
		move_image(info, MLX_KEY_DOWN);
	if (mlx_is_key_down(info->mlx, MLX_KEY_UP))
		move_image(info, MLX_KEY_UP);
	if (mlx_is_key_down(info->mlx, MLX_KEY_KP_ADD))
		zoom_image(info, MLX_KEY_KP_ADD);
	if (mlx_is_key_down(info->mlx, MLX_KEY_KP_SUBTRACT))
		zoom_image(info, MLX_KEY_KP_SUBTRACT);
	if (mlx_is_key_down(info->mlx, MLX_KEY_X))
		scale_z(info, MLX_KEY_X);
	if (mlx_is_key_down(info->mlx, MLX_KEY_Z))
		scale_z(info, MLX_KEY_Z);
}

void	ft_listen_to_alicia_keys_baby(void *info)
{
	translate(info);
}
