/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:11 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/01 16:42:25 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int first_commande(t_minishell *mini, t_cmd *cmds)
{
	pid_t	pid;

	mini->pipe[0] = (int *)malloc(sizeof(int) * 2);
	if (!mini->pipe[0])
		return (1);
	if (pipe(mini->pipe[0]) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (!pid)
	{
		close(mini->pipe[0][0]);
		process(mini, cmds, STDOUT_FILENO, mini->pipe[0][1]);
	}
	else
		close(mini->pipe[0][1]);
	return (0);
}

int	middle_comamndes(t_minishell *mini, t_cmd *cmds, int i)
{
	pid_t	pid;

	mini->pipe[i] = (int *)malloc(sizeof(int) * 2);
	if (!mini->pipe[i])
		return (1);
	if (pipe(mini->pipe[i]) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (!pid)
	{
		close(mini->pipe[i][0]);
		process(mini, cmds, mini->pipe[i - 1][0], mini->pipe[i][1]);
	}
	else
	{
		close(mini->pipe[i][1]);
		close(mini->pipe[i - 1][0]);
	}
	return (0);
}

int	last_commande(t_minishell *mini, t_cmd *cmds, int i)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
		process(mini, cmds, mini->pipe[i - 1][0], STDOUT_FILENO);
	else
		close(mini->pipe[i - 1][0]);
	return (0);
}

int     multi_process(t_minishell *mini, t_cmd *cmds)
{
	int	status;
	int	i;

	red_process(mini, cmds);
	first_commande(mini, cmds);
	t_cmd	*tmp = cmds->next;
	i = 1;
	while (tmp->next)
	{
		red_process(mini, tmp);
		middle_comamndes(mini, tmp, i);
		tmp = tmp->next;
		i++;
	}
	red_process(mini, tmp);
	last_commande(mini, tmp, i);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	return (status);
}
