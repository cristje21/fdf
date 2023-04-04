/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:41:03 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/04 16:42:58 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fdf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/errno.h>

void	new_line(t_lines **head, int *line)
{
	t_lines	*new;
	t_lines	*tmp;

	new = malloc(sizeof(t_lines));
	if (new == NULL)
		ft_error("Error: malloc failure", errno);
	new->line = line;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	make_array(t_lines **head, t_info *info)
{
	t_lines	*tmp;
	int		count;
	int		**result;

	tmp = *head;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	result = malloc((count + 1) * sizeof(int *));
	if (result == NULL)
		ft_error("Error: malloc failure", errno);
	result[count] = NULL;
	count = 0;
	while (*head)
	{
		tmp = *head;
		result[count++] = (*head)->line;
		*head = tmp->next;
		free(tmp);
	}
	info->height = count;
	info->matrix = result;
}

int	fill_array(int i, char *s, int *result, int *count)
{
	while (s[i] == ' ')
		i++;
	if (s[i] && s[i] != '\n')
		result[*count] = fdf_atoi(&s[i]);
	while (s[i] && s[i] != ' ')
		i++;
	*count = *count + 1;
	return (i);
}

void	make_list(char *s, t_info *info, int fd)
{
	int		i;
	int		count;
	int		*result;
	t_lines	*head;

	head = NULL;
	while (s)
	{
		i = 0;
		count = 0;
		result = malloc(info->width * sizeof(int));
		if (result == NULL)
			ft_error("Error: malloc failure", errno);
		while (s[i] && count < info->width)
			i = fill_array(i, s, result, &count);
		while (s[i] == ' ')
			i++;
		if (count != info->width || (s[i] && s[i] != '\n'))
			ft_error("Error: wrong map format\n", -2);
		free(s);
		new_line(&head, result);
		s = get_next_line(fd);
	}
	make_array(&head, info);
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
	info->width = get_width(s);
	make_list(s, info, fd);
	return (info);
}
