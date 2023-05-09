/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   misc_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:42:08 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/05/07 14:36:41 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int	to_add(char x)
{
	if (x >= '0' && x <= '9')
		return (x - '0');
	else if (x >= 'a' && x <= 'f')
		return (x - 'a' + 10);
	else if (x >= 'A' && x <= 'F')
		return (x - 'A' + 10);
	else
		return (-1);
}

int	ft_xtoi(char *hex)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!hex)
		return (-1);
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	while (hex[i] && hex[i] != ' ' && hex[i] != '\n')
	{
		res = res * 16 + to_add(hex[i]);
		i++;
	}
	return (res);
}

t_matrix	*new_node(int x, int y, int z, int color)
{
	t_matrix	*new;

	new = malloc(sizeof(t_matrix));
	if (new == NULL)
		ft_error("Error: malloc failure", errno);
	new->x = x;
	new->y = y;
	new->z = z;
	new->color = color;
	new->next = NULL;
	new->down = NULL;
	return (new);
}

void	add_back(t_matrix **head, t_matrix *to_add)
{
	t_matrix	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = to_add;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}
