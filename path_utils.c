/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:58 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/24 14:45:33 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>

static void	ft_write_error_msg(char *str, t_env *s_env);

void	ft_try_paths(char **paths, char **args, t_env *s_env)
{
	char	*cmd;
	int		i;

	i = 0;
	if (!args || !args[i])
		return ;
	while (paths[i])
	{
		if (!ft_strchr(args[0], '/'))
			cmd = ft_strjoin(paths[i], args[0]);
		else
			cmd = args[0];
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
		{
			close(s_env->term_in);
			close(s_env->term_out);
			execve(cmd, args, s_env->env);
		}
		if (!ft_strchr(args[0], '/'))
			free(cmd);
		i++;
	}
	ft_write_error_msg(args[0], s_env);
	exit(127);
}

char	**ft_get_paths(char **env)
{
	char	**paths;
	char	*path;
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (!line)
	{
		line = ft_strnstr(env[i], "PATH=", 5);
		i++;
		if (!env[i])
			paths = ft_calloc(sizeof(*paths), 1);
		if (!env[i])
			return (paths);
	}
	path = ft_substr(line, 5, ft_strlen(line) - 5);
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
		ft_strjoin_free(&paths[i++], "/");
	return (paths);
}

static void	ft_write_error_msg(char *str, t_env *s_env)
{
	ft_putstr_fd(SHELL_NAME, 2);
	if (isatty(s_env->term_in))
		ft_putstr_fd(": ", 2);
	else
		ft_print_line_nr(s_env->line_nr);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}
