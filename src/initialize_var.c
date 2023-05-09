/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_var.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/07 15:40:57 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/09 14:24:27 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	get_unit_length(t_info *info)
{
	int	x;

	if (W <= H)
		x = W;
	else
		x = H;
	if (info->width > info->height)
		info->unit_length = ((x >> 1) - (PAD)) / info->width;
	else
		info->unit_length = ((x >> 1) - (PAD)) / info->height;
	if (info->unit_length < 3)
		info->unit_length = 3;
	info->origin[0] = W >> 1;
	info->origin[1] = H >> 1;
}

void	reassign_coords(t_info *info, t_matrix *matrix, int flag)
{
	matrix->x -= (info->width >> 1);
	matrix->y -= (info->height >> 1);
	if (matrix->next && flag)
		reassign_coords(info, matrix->next, 1);
	if (matrix->down)
		reassign_coords(info, matrix->down, 0);
}
