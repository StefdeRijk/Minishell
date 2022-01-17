/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:35 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/17 13:33:13 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "Libft/libft.h"
#include "minishell.h"

int	is_int(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

int	ft_exit(int nr_parts, t_part *parts, int line_nr)
{
	if (nr_parts == 1)
		exit(0);
	if (!is_int(parts[1].part))
	{
		ft_exit_error(0, parts[1].part, line_nr);
		exit(255);
	}
	if (nr_parts > 2)
	{
		ft_exit_error(1, "", line_nr);
		return (1);
	}
	else
		exit(ft_atoi(parts[1].part));
}
