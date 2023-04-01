/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:41:03 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/01 19:44:02 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>

int	fdf_atoi(const char *str)
{
	int		i;
	long	res;
	char	*s;
	int		m;

	s = (char *)str;
	res = 0;
	i = whitespace(s);
	m = 1;
	if (s && s[i] == '-')
	{
		m = -1;
		i++;
	}
	while (s && s[i] == '0' && s[i + 1] == '0')
		i++;
	if (!s || !s[i] || ft_strlen(s + i) > 10)
		return (ft_error("Error: input is not an integer\n"), EXIT_FAILURE);
	while (s[i] <= '9' && s[i] >= '0')
		res = res * 10 + s[i++] - '0';
	res *= m;
	if ((res <= 2147483647 && res >= -2147483648) && !s[i])
		return (res);
	return (ft_error("Error: input is not an integer\n"), EXIT_FAILURE);
}

typedef struct s_matrix
{
	int				*line;
	struct s_matrix	*next;
}					t_lines;



int	parse_map(char *map, int **matrix)
{
	int		fd;
	char	**s;
	char	*tmp;
	t_lines	*start;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_error("Error: failed to open map");
	tmp = get_next_line(fd);
	if (tmp == NULL)
		ft_error("Error: malloc failed");
	while (tmp)
	{
		s = ft_split(tmp, ' ');
		if (s == NULL)
			ft_error("Error: malloc failed");
		else if (*s == NULL)
			ft_error("Error: no input\n");
		while ()
	}
	return (0);
}
