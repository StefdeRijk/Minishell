/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:05 by sde-rijk      #+#    #+#                 */
/*   Updated: 2021/12/27 15:35:51 by daniel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "bash"

enum e_part_type {
	SPACES,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	NORMAL,
	SPECIAL
};

typedef struct s_part {
	char				*part;
	enum e_part_type	type;
}	t_part;

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;
	int		iter;
	int		len;
	int		begin;
	int		end;

	char	**commands;
	char	**paths;

	char	*cmd;
	char	**cmd_flag;
}	t_pipe;

typedef struct s_env
{
	char	**env;
	int		size;
}	t_env;

char	**ft_get_commands(char **argv, int len, t_pipe *pipex);
char	**ft_get_commands_parts(int nr_parts, t_part *parts, t_pipe *pipex);
void	ft_close_all_pipes(t_pipe pipex, int *pipefd);
void	ft_child_process(t_pipe pipex, int *pipefd, t_env *s_env, \
t_part *parts);
t_pipe	ft_set_io(int nr_parts, t_part *parts, t_pipe pipex);
int		ft_pipex(int nr_parts, t_part *parts, t_env *s_env);
t_pipe	ft_get_pipes(t_pipe pipex, int *pipefd);

void	signals(void);

int		ft_echo(int nr_parts, t_part *parts);
int		ft_pwd(void);
int		ft_cd(t_part *parts);
int		ft_env(char **envp);
int		ft_export(t_part *parts, t_env *s_env);
int		ft_exit(int nr_parts, t_part *parts);
void	copy_env(char **envp, t_env *s_env);
int		ft_unset(t_part *parts, t_env *s_env);
char	*ft_wildcard(char *args, int *wild_quoted);
char	**ft_split_unquoted(char const *s, char c, const int *quoted);

int		ft_executable(int nr_parts, t_part *parts, t_env *s_env);
void	expand_args(char **sp, int last_exit_status, t_env *s_env, int niq);
int		ft_export_print(char **envp);
t_part	*quote_split(char *s);
void	expand_unquoted_args(t_part *parts, int last_exit_status, t_env *s_env);
char	**parts_to_strings(t_part *parts);
t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env);
void	ft_free_parts(t_part *parts);
int		count_parts(t_part *s);
int		replace_parts(t_part **parts, int i);
void	ft_replace(char **sp, int start, int len, char *rep);

int		redirect_in(int nr_parts, t_part *parts, t_env *s_env, int *exec);
int		redirect_out(int nr_parts, t_part *parts, t_env *s_env, int *exec);
int		redirect_out_app(int nr_parts, t_part *parts, t_env *s_env, int *exec);
void	ft_try_paths(char **paths, char **args, t_env *s_env, t_part *parts);
int		redirect_here_doc(int nr_parts, t_part *parts, t_env *s_env, int *exec);
char	**ft_get_paths(char **env);
void	ft_redir_args(char **args, int nr_parts, t_part *parts, t_env *s_env);
void	expand_wildcard(t_part **parts, int **wild_quoted);

int		is_built_in(char *str, int nr_parts, t_part *parts, t_env *s_env);

int		ft_syntax_error(t_part *parts, int i);
int		ft_redir_error(char *str, char *str2);
int		ft_invalid_identifier(t_part *parts, int i);

void	print_parts(t_part *parts);
void	print_strs(char **strs);
#endif
