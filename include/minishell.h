/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunlee2 <seunlee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 18:58:58 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/15 21:28:01 by seunlee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include "libft.h"

typedef struct s_parse
{
	int	i;
	int	start;
	int	quote;
}	t_parse;

enum	e_type
{
	CHUNK,
	SINGL,
	REDIR,
};

enum	e_pars
{
	NORM,
	SPCE,
	SINQ,
	DOUQ,
	DOLR,
	PIPE,
	DPIP,
	RIGT,
	DRGT,
	LEFT,
	DLFT
};

enum	e_sigs
{
	USR,
	DFL,
	IGN,
};

typedef struct s_list
{
	char			*str;
	int				type;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_file;
	int				is_pipe;
	int				fd[2];
	int				infile_fd;
	int				outfile_fd;
	int				is_dlft;
	struct s_redir	*redir;
	struct s_redir	*l_redir;
	struct s_redir	*r_redir;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_envp
{
	char			*str;
	char			**dict;
	struct s_envp	*prev;
	struct s_envp	*next;
}	t_envp;

typedef struct s_redir
{
	int				type;
	char			*str;
	struct s_redir	*next;
}	t_redir;

typedef struct s_mini
{
	t_list	*list;
	t_cmd	*cmd;
	t_envp	*envp;
}	t_mini;

char	*get_env_home(t_mini *m);
void	make_oldpwd(t_mini *m, char *now);
void	builtin_cd(t_mini *m, t_cmd *cmd);

void	builtin_center(t_mini *m, t_cmd *cmd);
void	builtin_echo(t_cmd *cmd);
void	builtin_env(t_mini *m, t_cmd *cmd);
void	builtin_exit(t_cmd *cmd);
void	builtin_pwd(void);
void	builtin_export(t_mini *m, t_cmd *cmd);
void	builtin_unset(t_mini *m, t_cmd *cmd);
int		is_builtin(char *str);

void	check_validation(int argc, char **argv);

int		chk_file_dir(t_cmd *cmd);
int		chk_file_exist(t_cmd *cmd, char **file_dir);
char	**chk_path(t_mini *m);
char	*str_join(char *a, char *b);

int		chk_right_redir(t_redir *r, t_cmd *cmd);
int		chk_drgt_redir(t_redir *r, t_cmd *cmd);
int		chk_r_redir(t_cmd *cmd);

int		chk_left_redir(t_redir *r, t_cmd *cmd);
int		chk_dlft_redir(t_redir *r, t_cmd *cmd);
int		chk_l_redir(t_cmd *cmd);

void	exec(t_mini *m);
void	exec_nopipe(t_mini *m);

int		get_envp_len(t_mini *m);
char	**make_envp(t_mini *m);

int		set_in_out_while(t_cmd *cmd);
void	set_in_out(t_cmd *cmd);

void	close_fd(t_cmd *cmd);
void	fork_child(t_mini *m, t_cmd *cmd);
void	do_fork(t_mini *m, t_cmd *cmd);

void	set_input_termios(void);
char	*make_path(void);
void	wait_child(int cnt_cat, int not_cat);
int		do_readline(t_mini *m);

t_envp	*init_envp(char **envp, int idx, int len);
void	init(t_mini *m, char **envp);

int		check_str_type(char curr);
int		check_cmd_type(char line);

t_cmd	*cmd_lstnew(void);
void	cmd_add_node(char **args, int is_pipe, t_redir *redir, t_cmd *cmd);

char	*merge_cmd_str(t_list *curr, char *str);
char	**make_cmd_array(t_list *curr);
int		get_cmd_list_size(t_list *list);
void	get_cmd_list(t_mini *m);
t_redir	*get_last_redir(t_redir *redir);

t_list	*lstnew(void);
t_redir	*lstnew_redir(void);
void	add_node(char *str, int type, t_list *list);
void	add_redir(char *str, int type, t_redir *redir);

char	*trans_str(t_envp *envp, char *str);
char	*process_dollar_sign(t_mini *m, char *str, int *i, char *chunk);
char	*get_prev_exit_code(char *chunk);
char	*get_chunk_str(t_mini *m, char *str);

void	get_chunk_index(t_parse *par, char *line, int type);
void	get_chunk(t_parse *par, char *line, t_mini *m);
void	get_redirection(t_parse *par, char *line, t_mini *m);
void	get_single_character(t_parse *par, char *line, t_mini *m);
int		parse(char *line, t_mini *m);

void	merge_norm(t_list *list);
void	make_redir_l_r(t_cmd *curr, char *tmp);

int		token_error(t_mini *m, t_parse *par);
int		check_parse_error(t_list *curr, t_list *last, char *tmp);
int		check_redir_str(t_redir *redir);

void	signal_handler(int signo);
void	process_signal(int cntl_c, int cntl_back);

void	str_error_handler(char *cmd, char *opt, char *str, int exit_code);

void	free_all(t_mini *m);
void	free_list(t_mini *m);
void	free_arr2(char **str);
void	free_cmd(t_mini *m);
void	free_while(char *line, t_mini *m);

char	*ft_newjoin(char const *s1, char const *s2);
char	*ft_slushjoin(char const *s1, char const *s2);

void	ft_free(char **str);
char	*ft_strndup(const char *src, size_t size);
int		is_space(char *line);
char	*ft_strjoin_char(char *str, char c);

int		ft_strcmp(char *s1, char *s2);
int		get_arr2_len(char **arr);
int		is_env(t_mini *m, char *key);
int		atoi_flag(const char *str, int *flag);

t_envp	*get_last_envp(t_mini *m);
t_list	*get_last_list(t_list *list);
t_cmd	*get_last_cmd(t_cmd *list);

#endif
