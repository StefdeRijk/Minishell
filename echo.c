/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:56 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/11 10:40:34 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_echo(int nr_parts, t_part *parts)
{
	int	i;

	i = 1;
	if (!&parts[1] || !parts[1].part)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (!ft_strcmp(parts[i].part, "-n"))
		i++;
	while (i < nr_parts)
	{
		if (write(1, parts[i].part, ft_strlen(parts[i].part)) < 0)
			return (1);
		if (i < nr_parts - 1)
		{
			if (write(1, " ", 1) < 0)
				return (1);
		}
		i++;
	}
	if (ft_strcmp(parts[1].part, "-n"))
	{
		if (write(1, "\n", 1) < 0)
			return (1);
	}
	return (0);
}
