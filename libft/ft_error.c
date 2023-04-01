/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/01 18:49:13 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/04/01 18:53:51 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/errno.h>

void	ft_error(char *msg)
{
	if (errno != 0)
	{
		perror(msg);
		exit(errno);
	}
	else if (msg)
		write(2, msg, ft_strlen(msg));
	else
		write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
