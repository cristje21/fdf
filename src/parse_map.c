/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:41:03 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/03 21:49:46 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fdf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/errno.h>

void	new_line(s_lines **head, int *line)
{
	s_lines	*new;
	s_lines	*tmp;

	new = malloc(sizeof(s_lines));
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

int	**make_array(s_lines **head)
{
	s_lines	*tmp;
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
	return (result);
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

int	**make_list(char *s, int width, int fd)
{
	int		i;
	int		count;
	int		*result;
	s_lines	*head;

	head = NULL;
	while (s)
	{
		i = 0;
		count = 0;
		result = malloc(width * sizeof(int));
		if (result == NULL)
			ft_error("Error: malloc failure", errno);
		while (s[i] && count < width)
			i = fill_array(i, s, result, &count);
		while (s[i] == ' ')
			i++;
		if (count != width || (s[i] && s[i] != '\n'))
			ft_error("Error: wrong map format\n", -2);
		free(s);
		new_line(&head, result);
		s = get_next_line(fd);
	}
	return (make_array(&head));
}

int	parse_map(int ***result, char *map)
{
	int		fd;
	int		width;
	char	*s;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error("Error: opening map", errno);
	s = get_next_line(fd);
	if (s == NULL)
		ft_error("Error: empty map\n", -1);
	width = get_width(s);
	*result = make_list(s, width, fd);
	return (width);
}
