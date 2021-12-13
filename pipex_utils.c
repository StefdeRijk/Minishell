/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:15:13 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/13 10:15:15 by sde-rijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "Libft/libft.h"
#include <stdlib.h>

char	**ft_get_commands(char **argv, int len, t_pipe *pipex)
{
	char	**commands;
	int		i;
	int		j;

	i = 0;
	j = 0;
	commands = ft_calloc((len + 1) * sizeof(char *), 1);
	while (j < len)
	{
		commands[j] = argv[i];
		i++;
		j++;
	}
	pipex->len = j + pipex->begin - pipex->end;
	return (commands);
}

void	ft_close_pipes(t_pipe pipex, int *pipefd)
{
	int	i;

	i = 0;
	while (i < (2 * (pipex.size - 1)))
	{
		close(pipefd[i]);
		i++;
	}
}
