/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_child.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:26 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/06 11:08:29 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

static void	ft_dup2(int first, int second);

static char	**ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env, char **commands);

static void	ft_check_filename(char **str, t_env *s_env, t_part *parts, int i);

void	ft_child_process(t_pipe pipex, int *pipefd, t_env *s_env, t_part *parts)
{
	if (pipex.iter == 0)
		ft_dup2(pipex.infile, pipefd[3]);
	else if (pipex.iter == pipex.size - 1)
		ft_dup2(pipefd[0], pipex.outfile);
	else
		ft_dup2(pipefd[0], pipefd[3]);
	if (pipex.iter != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	close(pipefd[2]);
	close(pipefd[3]);
	pipex.cmd_flag = ft_get_cmd_flag(parts, pipex, s_env, pipex.commands);
	ft_try_paths(pipex.paths, pipex.cmd_flag, s_env, parts);
}

static void	ft_dup2(int first, int second)
{
	if (dup2(first, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(errno);
	}
	if (dup2(second, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(errno);
	}
}

static char	**ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env, char **commands)
{
	char	**cmd;
	int		i;
	int		j;
	int		k;

	i = pipex.begin;
	j = 0;
	k = 0;
	cmd = ft_calloc((pipex.len + 1) * sizeof(char *), 1);
	while (j < pipex.iter)
	{
		if (!ft_strcmp(commands[i], "|") && parts[i].type == SPECIAL)
			j++;
		i++;
	}
	j = 0;
	if (pipex.begin)
		pipex.len -= pipex.end;
	if (!ft_strcmp(commands[i], "<") || \
	!ft_strcmp(commands[i], ">>") || !ft_strcmp(commands[i], ">"))
		ft_check_filename(commands + i, s_env, parts, i);
	while (commands[i] && i < pipex.len && (ft_strcmp(commands[i], "|") \
	|| parts[i].type != SPECIAL))
	{
		if (!ft_strcmp(commands[i], "<") || \
		!ft_strcmp(commands[i], ">>") || !ft_strcmp(commands[i], ">"))
		{
			check_for_redirections(&k, parts + i + 1, s_env, i + 2);
			if (open(commands[i + 1], O_RDONLY) < 0)
			{
				ft_redir_error(SHELL_NAME, commands[i + 1], s_env->line_nr);
				exit(0);
			}
			i += 2;
		}
		else
			cmd[j++] = ft_strdup(commands[i++]);
	}
	if (i == pipex.len + pipex.end)
		free(commands[i]);
	return (cmd);
}

static void	ft_check_filename(char **str, t_env *s_env, t_part *parts, int i)
{
	int	fd;

	if (!str[1])
		ft_syntax_error(parts, 0, s_env->line_nr, "newline");
	else if (parts[i + 1].type == SPECIAL)
		ft_syntax_error(parts, 0, s_env->line_nr, str[1]);
	else
	{
		if (!ft_strcmp(str[0], "<"))
			fd = open(str[1], O_RDONLY);
		else
			fd = open(str[1], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			ft_redir_error(SHELL_NAME, str[1], s_env->line_nr);
		else
			close(fd);
	}
	exit(0);
}
