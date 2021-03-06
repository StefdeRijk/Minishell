/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:35 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 14:28:10 by sde-rijk      ########   odam.nl         */
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

int	ft_exit(int nr_parts, t_part *parts, t_env *s_env)
{
	if (isatty(s_env->term_in))
		ft_putstr_fd("exit\n", 1);
	if (nr_parts == 1)
		exit(0);
	if (!is_int(parts[1].part))
	{
		ft_exit_error(0, parts[1].part, s_env);
		exit(255);
	}
	if (nr_parts > 2)
	{
		ft_exit_error(1, "", s_env);
		return (1);
	}
	else
		exit(ft_atoi(parts[1].part));
}
