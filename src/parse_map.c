/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:41:03 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/01 22:07:39 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fdf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/errno.h>

// void	print_everything(t_matrix *head)
// {
// 	t_matrix	*tmp;

// 	tmp = head;
// 	while (head)
// 	{
// 		tmp = head;
// 		while (tmp)
// 		{
// 			ft_printf("x:%d, y:%d, z:%d, color:%d\n", tmp->x, tmp->y, tmp->z, tmp->color);
// 			tmp = tmp->next;
// 		}
// 		ft_printf("\n");
// 		head = head->down;
// 	}
// }

void	get_line(char *s, int y, t_matrix **head)
{
	int			i;
	int			x;
	int			z;
	t_matrix	*to_add;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\n')
			i++;
		if (s[i])
			z = fdf_atoi(&s[i]);
		while (s[i] && s[i] != ' ' && s[i] != ',')
			i++;
		if (s[i] == ',')
			to_add = new_node(x, y, z, (ft_xtoi(&s[i + 1]) << 8) + 255);
		else
			to_add = new_node(x, y, z, 0xFFFFFFFF);
		while (s[i] && s[i] != ' ')
			i++;
		add_back(head, to_add);
		x++;
	}
}

void	stream_line(t_matrix *bottom, t_matrix *top)
{
	while (top)
	{
		top->down = bottom;
		if (!bottom)
			ft_error("Error: map format\n", -1);
		bottom = bottom->next;
		top = top->next;
	}
	if (bottom)
	{
		ft_printf("bottom->x: %d\nbottom->y: %d\nbottom->z: %d\n", bottom->x, bottom->y, bottom->z);
		ft_error("Error: map format\n", -1);
	}
	
}

void	make_linked_list(int fd, char *s, t_info *info)
{
	t_matrix	*y_head;
	t_matrix	*tmp;
	int			y;

	y = 0;
	while (s)
	{
		y_head = NULL;
		get_line(s, y, &y_head);
		if (!y)
			info->matrix = y_head;
		else
			stream_line(y_head, tmp);
		tmp = y_head;
		free(s);
		s = get_next_line(fd);
		y++;
	}
	info->height = y;
	info->width = get_width(info->matrix);
}

t_info	*parse_map(char *map)
{
	int		fd;
	char	*s;
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		ft_error("Error: malloc failure", errno);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error("Error: opening map", errno);
	s = get_next_line(fd);
	if (s == NULL)
		ft_error("Error: empty map\n", -1);
	make_linked_list(fd, s, info);
	info->z_scaler = 0;
	return (info);
}
