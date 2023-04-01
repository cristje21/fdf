/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 14:25:57 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/01 19:09:24 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <MLX42.h>
#include <math.h>

static void	set_var(int *inc, int *start, int *end)
{
	if (start[0] >= end[0])
		inc[0] = -1;
	else
		inc[0] = 1;
	if (start[1] >= end[1])
		inc[1] = -1;
	else
		inc[1] = 1;
}

static void	bresenham(int *start, int *end, int color, mlx_image_t *img)
{
	int	longest;
	int	shortest;
	int	numerator;
	int	inc[2];
	int	i;

	i = 0;
	set_var(inc, start, end);
	longest = abs(start[0] - end[0]);
	shortest = abs(start[1] - end[1]);
	numerator = longest >> 1;
	while (i++ < longest)
	{
		mlx_put_pixel(img, start[0], start[1], color);
		numerator += shortest;
		if (numerator >= longest)
		{
			numerator -= longest;
			start[1] += inc[1];
		}
		start[0] += inc[0];
	}
}

void	put_line(int *start, int *end, int color, mlx_image_t *img)
{
	int	tmp;

	if (abs(start[0] - end[0]) > abs(start[1] - end[1]))
	{
		tmp = start[0];
		start[0] = start[1];
		start[1] = tmp;
		tmp = end[0];
		end[0] = end[1];
		end[1] = tmp;
	}
	bresenham(start, end, color, img);
}
