/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_args.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:31 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/25 10:54:53 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "stdio.h"
#include "minishell.h"

void	ft_replace(char **sp, int start, int len, char *rep)
{
	char	*new;
	int		new_length;
	char	*last_part;

	if (!rep)
		rep = "";
	new_length = ft_strlen(*sp) + ft_strlen(rep) - len + 1;
	last_part = *sp + start + len;
	new = ft_calloc(new_length, 1);
	ft_memcpy(new, *sp, start);
	ft_memcpy(new + start, rep, ft_strlen(rep));
	ft_memcpy(new + start + ft_strlen(rep), last_part, \
		ft_strlen(last_part));
	free(*sp);
	*sp = new;
}

char	*ft_search_name(t_env *s_env, char *envname, int envlen)
{
	int		i;

	i = 0;
	while (s_env->env[i])
	{
		if (!ft_strncmp(s_env->env[i], envname, envlen) && \
		s_env->env[i][envlen] == '=')
			return (s_env->env[i] + envlen + 1);
		i++;
	}
	return (NULL);
}

int	ft_insert_exit_status(char **sp, int i, int last_exit_status)
{
	char	*env;

	if ((*sp)[i] == '?')
	{
		env = ft_itoa(last_exit_status);
		ft_replace(sp, i - 1, 2, env);
		free(env);
		return (1);
	}
	return (0);
}

int	expand_args(char **sp, int last_exit_status, t_env *s_env,
		int next_is_quoted)
{
	int			i;
	char		*env;
	size_t		envlen;

	i = 0;
	while ((*sp)[i])
	{
		i++;
		if ((*sp)[i - 1] == '$')
		{
			if (ft_insert_exit_status(sp, i, last_exit_status))
				continue ;
			envlen = get_env_name_length((*sp) + i);
			if (envlen == 0 && !next_is_quoted)
				continue ;
			env = ft_search_name(s_env, *sp + i, envlen);
			if (!env && i == 1 && envlen == ft_strlen((*sp) + i))
				return (1);
			if (!env)
				env = "";
			ft_replace(sp, --i, envlen + 1, env);
		}
	}
	return (0);
}
