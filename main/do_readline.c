/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonggoc <seonggoc@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:08:35 by seunlee2          #+#    #+#             */
/*   Updated: 2023/11/17 11:42:39 by seonggoc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern long long	g_exit_code;

char	*make_path(void)
{
	char	*pwd;
	char	*path;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		str_error_handler("pwd", NULL,
			"current working directory get error", 2);
		exit(g_exit_code);
	}
	path = ft_strjoin(pwd, " > ");
	free(pwd);
	return (path);
}

void	wait_child(int cnt_cat, int not_cat)
{
	int	i;
	int	signo;
	int	status;

	i = 0;
	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			if (!(cnt_cat && not_cat))
				g_exit_code = 128 + signo;
			else
				g_exit_code = WEXITSTATUS(status);
		}
		else
			g_exit_code = WEXITSTATUS(status);
	}
}

int	chk_cnt_cat(t_cmd *cmd, int *not_cat)
{
	t_cmd	*c;
	int		cnt;

	cnt = 0;
	c = cmd;
	while (c)
	{
		if (!(c->args && c->args[0]))
			break ;
		if (!ft_strcmp(c->args[0], "cat"))
			cnt++;
		if (!(c->next))
		{
			if (ft_strcmp(c->args[0], "cat"))
				*not_cat = 1;
		}
		c = c->next;
	}
	return (cnt);
}

void	exec_with_parse(t_mini *m, char *line)
{
	char	pipe_no;
	int		cnt_cat;
	int		not_cat;

	pipe_no = parse(line, m);
	if (pipe_no > 0)
		exec(m);
	else if (pipe_no == 0)
		exec_nopipe(m);
	not_cat = 0;
	cnt_cat = chk_cnt_cat(m->cmd, &not_cat);
	wait_child(cnt_cat, not_cat);
	process_signal(USR, USR);
	free_while(line, m);
}

int	do_readline(t_mini *m)
{
	char	*line;

	while (1)
	{
		line = readline("minishell > ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (!ft_strlen(line) && ft_strcmp(line, "\n"))
		{
			free(line);
			continue ;
		}
		if (*line != '\0')
			add_history(line);
		exec_with_parse(m, line);
		free(m->list->str);
	}
	free_all(m);
	return (0);
}
