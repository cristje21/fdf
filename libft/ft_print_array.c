/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print_array.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/30 20:02:31 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/01/30 20:02:33 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%d: %s\n", i, array[i]);
		i++;
	}
}
