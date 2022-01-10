/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:43 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/10 10:23:30 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int		ft_pipex_pipe(t_pipe pipe, t_env *s_env, t_part *parts);

static int		ft_get_size_parts(t_part *parts);

static int		ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd);

static int		ft_wait_for_child(t_pipe pipex, pid_t child);

int	ft_pipex(int nr_parts, t_part *parts, t_env *s_env)
{
	t_pipe	pipex;
	int		status;
	int		term_out;
	int		term_in;

	pipex.begin = 0;
	pipex.end = 0;
	term_out = dup(STDOUT_FILENO);
	term_in = dup(STDIN_FILENO);
	if (term_out < 0 || term_in < 0)
		perror("dup");
	pipex = ft_set_io(nr_parts, parts, pipex);
	if (pipex.infile < 0 || pipex.outfile < 0)
		return (ft_open_error(pipex, term_out, parts, nr_parts));
	pipex.len = nr_parts + pipex.begin - pipex.end;
	pipex.size = ft_get_size_parts(parts);
	status = ft_pipex_pipe(pipex, s_env, parts);
	close(pipex.infile);
	close(pipex.outfile);
	if (dup2(term_out, STDOUT_FILENO) < 0 || dup2(term_in, STDIN_FILENO) < 0)
		perror("dup2");
	close(term_in);
	close(term_out);
	return (status);
}

static int	ft_get_size_parts(t_part *parts)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (parts[i].part)
	{
		if (is_pipe(parts[i]))
			count++;
		i++;
	}
	return (count);
}

static int	ft_pipex_pipe(t_pipe pipex, t_env *s_env, t_part *parts)
{
	int		pipefd[4];
	int		status;

	pipex.paths = ft_get_paths(s_env->env);
	pipex.iter = 0;
	status = ft_execute_pipes(pipex, s_env, parts, pipefd);
	ft_free_strs(pipex.paths);
	return (WEXITSTATUS(status));
}

static int	ft_execute_pipes(t_pipe pipex, t_env *s_env, \
t_part *parts, int *pipefd)
{
	pid_t	child;

	child = 0;
	while (pipex.iter < pipex.size)
	{
		if (pipex.size > 1 && pipe(pipefd + 2) < 0)
			perror("Pipe: ");
		if (pipex.size > 1)
		{
			child = fork();
			if (child < 0)
				perror("Fork: ");
			if (child == 0)
				ft_child_process(pipex, pipefd, s_env, parts);
			if (pipex.iter > 0)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			pipefd[0] = pipefd[2];
			pipefd[1] = pipefd[3];
		}
		else
			ft_child_process(pipex, pipefd, s_env, parts);
		pipex.iter++;
	}
	if (pipex.size > 1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	return (ft_wait_for_child(pipex, child));
}

static int	ft_wait_for_child(t_pipe pipex, pid_t child)
{
	int	status;

	while (pipex.iter > 0)
	{
		waitpid(-1, &status, 0);
		pipex.iter--;
	}
	waitpid(child, &status, 0);
	return (status);
}
