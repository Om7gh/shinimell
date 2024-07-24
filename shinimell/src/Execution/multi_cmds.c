/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:56:11 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/24 16:06:23 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	first_commande(t_minishell *mini, t_cmd *cmds)
{
	pid_t	pid;

	mini->pipe[0] = malloc(sizeof(int) * 2);
	if (pipe(mini->pipe[0]) == -1)
		return (perror("pipe"), ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (pid == 0)
	{
		close(mini->pipe[0][0]);
		dup2(mini->pipe[0][1], 1);
		close(mini->pipe[0][1]);
		my_execve(mini, cmds);
	}
	else
			close(mini->pipe[0][1]);
	return (SUCCESS);
}
int middle_commandes(t_minishell *mini, t_cmd *cmds)
{
	int	i;
	int	cmds_nbr;
	pid_t	pid;

	i = 0;
	cmds_nbr = node_len(mini->cmd);
	while (++i < cmds_nbr - 1)
	{
		mini->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(mini->pipe[i]) == -1)
			return (perror("pipe"), ERROR);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), ERROR);
		if (pid == 0)
		{
			close(mini->pipe[i - 1][1]);
			dup2(mini->pipe[i - 1][0], 0);
			close(mini->pipe[i - 1][0]);
			close(mini->pipe[i][0]);
			dup2(mini->pipe[i][1], 1);
			close(mini->pipe[i][1]);
			my_execve(mini, cmds);
		}
		else
		{
			close(mini->pipe[i][1]);
			close(mini->pipe[i - 1][0]);
		}
		i++;
	}
	return (SUCCESS);
}

int last_commande(t_minishell *mini, t_cmd *cmd)
{
	pid_t	pid;
	int	cmds_nbr;

	cmds_nbr = node_len(mini->cmd);
	mini->pipe[cmds_nbr - 1] = (int *)malloc(sizeof(int) * 2);
	if (pipe(mini->pipe[cmds_nbr - 1]) == -1)
		return (perror("pipe"), ERROR);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), ERROR);
	if (!pid)
	{
		close(mini->pipe[cmds_nbr - 2][1]);
		dup2(mini->pipe[cmds_nbr - 2][0], 0);
		close(mini->pipe[cmds_nbr - 1][0]);
		my_execve(mini, cmd);
	}
	else
	{
		close(mini->pipe[cmds_nbr - 1][1]);
		close(mini->pipe[cmds_nbr - 1][0]);
	}
	
	return (SUCCESS);
}


int     multi_process(t_minishell *mini, t_cmd *cmds)
{
	int	status;
	first_commande(mini, cmds);
	middle_commandes(mini, cmds);
	last_commande(mini, cmds);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	return (status);
}
