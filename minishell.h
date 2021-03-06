/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-rijk <sde-rijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/13 10:16:05 by sde-rijk      #+#    #+#                 */
/*   Updated: 2022/01/25 11:25:44 by dnoom         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "bash"

# include <unistd.h>

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
	int		len;
	int		size;
	int		iter;

	int		pipefd[4];

	char	**paths;

	char	*cmd;
	t_part	*cmd_flag;
}	t_pipe;

typedef struct s_env
{
	char	**env;
	int		size;
	int		line_nr;
	int		term_in;
	int		term_out;
}	t_env;

int		ft_pipex(int nr_parts, t_part *parts, t_env *s_env);
pid_t	ft_do_forks(t_pipe pipex, t_part *parts, t_env *s_env, int status);
t_part	*ft_get_cmd_flag(t_part *parts, t_pipe pipex, \
t_env *s_env, int *status);
t_part	*get_commands_between_pipes(t_part *parts, t_pipe pipex, \
t_env *s_env);
int		ft_find_first_command(t_pipe pipex, t_part *parts);

int		ft_is_redir(t_part part);
int		is_pipe(t_part part);
int		is_input_redir(t_part part);
int		is_output_redir(t_part part);
int		is_here_doc(t_part part);

int		ft_do_redir(t_part *parts, t_env *s_env, int i);
int		here_doc(char *final, t_env *s_env, t_part *parts);
char	*next_line(t_env *s_env);
int		return_from_sigint(char *line, char **args, int term, t_env *s_env);
void	add_to_args_free(char ***args_p, char *line);

void	signals(void);
void	sigint_handler(int sig);
void	sigint_handler_nonl(int sig);
void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);

int		ft_echo(int nr_parts, t_part *parts);
int		ft_pwd(t_env *s_env);
int		ft_cd(t_part *parts, t_env *s_env);
int		ft_env(char **envp);
int		ft_export(t_part *parts, t_env *s_env);
int		ft_export_var(t_env *s_env, char *part, char *envname);
char	*get_prev_var(t_env *s_env, char *envname, int *i);
int		ft_exit(int nr_parts, t_part *parts, t_env *s_env);
int		ft_unset(t_part *parts, t_env *s_env);
void	copy_env(char **envp, t_env *s_env);

char	*ft_wildcard(char *args, int *wild_quoted);
char	**ft_split_unquoted(char const *s, char c, const int *quoted);

int		ft_executable(int nr_parts, t_part *parts, t_env *s_env);
void	ft_try_paths(char **paths, char **args, t_env *s_env);
char	**ft_get_paths(char **env);
void	ft_remove_part(t_part *parts);

t_part	*ft_shell_split(char *s, int last_exit_status, t_env *s_env);
t_part	*quote_split(char *s);
int		next_open_quote(char *s, int is_s_q, int is_d_q);
int		replace_arg(char **s, int *i, t_env *s_env, int *is_q);

int		expand_args(char **sp, int last_exit_status, t_env *s_env, \
			int next_is_quoted);
int		ft_insert_exit_status(char **sp, int i, int last_exit_status);
void	ft_expand_args(char **s, int last_exit_status, t_env *s_env);
void	expand_unquoted_args(t_part *parts, int last_exit_status, t_env *s_env);
void	expand_wildcard(t_part **parts, int **wild_quoted);
void	ft_replace(char **sp, int start, int len, char *rep);
int		replace_parts(t_part **parts, int i);
char	**parts_to_strings(t_part *parts);

int		count_parts(t_part *s);
void	ft_free_parts(t_part *parts);
int		get_env_name_length(char *env);
void	ft_free_env(t_env *s_env);

char	*ft_search_name(t_env *s_env, char *envname, int envlen);
int		is_built_in(char *str, int nr_parts, t_part *parts, t_env *s_env);
int		check_for_redirections(int *last_exit_status, t_part *parts, \
t_env *s_env, int nr_parts);
int		check_identifier(char *str, int unset);
void	expand_env(t_env *s_env);

int		ft_syntax_error(t_part *parts, int i, t_env *s_env, char *token);
int		ft_syntax_error_eof(t_env *s_env);
int		ft_redir_error(char *str, char *str2, t_env *s_env);
int		ft_invalid_identifier(t_part *parts, int i, t_env *s_env);
int		ft_exit_error(int too_many, char *arg, t_env *s_env);
void	ft_print_line_nr(int line_nr);
void	ft_print_shell_line(t_env *s_env);
int		ft_home_not_set(t_part *parts, int i, t_env *s_env, char *envvar);

void	print_parts(t_part *parts);
int		print_parts_error(t_part *parts);
void	print_strs(char **strs);
int		ft_export_print(char **envp);
#endif
