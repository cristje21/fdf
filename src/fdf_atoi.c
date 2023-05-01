/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf_atoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 21:47:47 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/27 16:55:16 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include "../libft/libft.h"

static int	whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '\n' || s[i] == '\t' || s[i] == '\v'
		|| s[i] == ' ' || s[i] == '\f' || s[i] == '\r')
		i++;
	return (i);
}

int	check_negative(char *s, int i, int *m)
{
	if (s && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
			*m = -1;
		i++;
	}
	else
		*m = 1;
	return (i);
}

int	check_overflow(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] <= '9' && s[i] >= '0')
		i++;
	if (i > 10)
		return (1);
	return (0);
}

int	fdf_atoi(const char *str)
{
	int		i;
	long	res;
	char	*s;
	int		m;

	s = (char *)str;
	res = 0;
	i = whitespace(s);
	i = check_negative(s, i, &m);
	while (s[i] == '0' && s[i + 1] == '0')
		i++;
	if (!s[i] || check_overflow(&s[i]))
		ft_error("Error: input is not an integer\n", -3);
	while (s[i] <= '9' && s[i] >= '0')
		res = res * 10 + s[i++] - '0';
	res *= m;
	if ((res <= 2147483647 && res >= -2147483648)
		&& (!s[i] || s[i] == ' ' || s[i] == '\n' || s[i] == ','))
		return (res);
	return (ft_error("Error: !input is not an integer\n", -3), EXIT_FAILURE);
}

int	get_width(t_matrix *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}
