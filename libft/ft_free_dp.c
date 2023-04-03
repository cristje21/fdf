/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_dp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 13:29:01 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/03 13:31:29 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_dp(char **s)
{
	int	i;
	
	i = 0;
	if (s)
	{
		while (s[i])
			free(s[i++]);
		free(s);
	}
}