/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:13:14 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/16 11:13:54 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"

int	ft_print_error(void)
{
	ft_putstr_fd("unset: not enough arguments\n", STDOUT_FILENO);
	return (1);
}

int	ft_unset(t_part *parts, t_env *s_env)
{
	char	*env;
	int		i;

	i = 0;
	if (!parts[1].part)
		return (ft_print_error());
	while (i < s_env->size && \
	!ft_strnstr(s_env->env[i], parts[1].part, ft_strlen(parts[1].part)))
		i++;
	if (i >= s_env->size)
		return (1);
	env = ft_strchr(s_env->env[i], '=');
	if (env != 0)
		ft_substr_free(&s_env->env[i], 0, \
		ft_strlen(s_env->env[i]) - ft_strlen(env));
	return (0);
}
