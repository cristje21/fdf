/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/30 14:25:57 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/09 13:41:48 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <MLX42.h>
#include <math.h>

// assumed that 0 to 0 is longest and 0 has to increment
static void	one(int *start, int *end, int color, mlx_image_t *img)
{
	int	longest;
	int	shortest;
	int	numerator;
	int	y_inc;

	longest = abs(start[0] - end[0]);
	shortest = abs(start[1] - end[1]);
	numerator = longest >> 1;
	if (start[1] < end[1])
		y_inc = 1;
	else
		y_inc = -1;
	while (start[0] < end[0])
	{
		if ((start[0] < W && start[0] >= 0) && (start[1] < H && start[1] >= 0))
			mlx_put_pixel(img, start[0], start[1], color);
		numerator += shortest;
		if (numerator >= longest)
		{
			numerator -= longest;
			start[1] += y_inc;
		}
		start[0]++;
	}
}

// here we assume that 1 to 1 is longest and 1 has to increment
static void	one_point_two(int *start, int *end, int color, mlx_image_t *img)
{
	int	longest;
	int	shortest;
	int	numerator;
	int	x_inc;

	longest = abs(start[1] - end[1]);
	shortest = abs(start[0] - end[0]);
	numerator = longest >> 1;
	if (start[0] < end[0])
		x_inc = 1;
	else
		x_inc = -1;
	while (start[1] < end[1])
	{
		if ((start[0] < W && start[0] >= 0) && (start[1] < H && start[1] >= 0))
			mlx_put_pixel(img, start[0], start[1], color);
		numerator += shortest;
		if (numerator >= longest)
		{
			numerator -= longest;
			start[0] += x_inc;
		}
		start[1]++;
	}
}

// assume that 0 has the biggest value and 0 to 0 has to decrement
static void	two(int *start, int *end, int color, mlx_image_t *img)
{
	int	longest;
	int	shortest;
	int	numerator;
	int	y_inc;

	longest = abs(start[0] - end[0]);
	shortest = abs(start[1] - end[1]);
	numerator = longest >> 1;
	if (start[1] < end[1])
		y_inc = 1;
	else
		y_inc = -1;
	while (start[0] > end[0])
	{
		if ((start[0] < W && start[0] >= 0) && (start[1] < H && start[1] >= 0))
			mlx_put_pixel(img, start[0], start[1], color);
		numerator += shortest;
		if (numerator >= longest)
		{
			numerator -= longest;
			start[1] += y_inc;
		}
		start[0]--;
	}
}

static void	two_point_two(int *start, int *end, int color, mlx_image_t *img)
{
	int	longest;
	int	shortest;
	int	numerator;
	int	x_inc;

	longest = abs(start[1] - end[1]);
	shortest = abs(start[0] - end[0]);
	numerator = longest >> 1;
	if (start[0] < end[0])
		x_inc = 1;
	else
		x_inc = -1;
	while (start[1] > end[1])
	{
		if ((start[0] < W && start[0] >= 0) && (start[1] < H && start[1] >= 0))
			mlx_put_pixel(img, start[0], start[1], color);
		numerator += shortest;
		if (numerator >= longest)
		{
			numerator -= longest;
			start[0] += x_inc;
		}
		start[1]--;
	}
}

void	put_line(int *start, int *end, int color, mlx_image_t *img)
{
	int	temp[2];

	temp[0] = start[0];
	temp[1] = start[1];
	if ((abs(start[0] - end[0]) >= abs(start[1] - end[1])) && start[0] <= end[0])
		one(temp, end, color, img);
	else if ((abs(start[0] - end[0]) >= abs(start[1] - end[1])) && start[0] > end[0])
		two(temp, end, color, img);
	else if ((abs(start[0] - end[0]) < abs(start[1] - end[1])) && start[1] <= end[1])
		one_point_two(temp, end, color, img);
	else if ((abs(start[0] - end[0]) < abs(start[1] - end[1])) && start[1] > end[1])
		two_point_two(temp, end, color, img);
}
