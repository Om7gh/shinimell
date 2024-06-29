/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:44:36 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/29 10:53:20 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void append_to_exec(t_cmd **cmds, t_cmd *cmd)
{
    t_cmd *head;

    if (!cmds || !cmd)
        return;
    if (!*cmds)
    {
        *cmds = cmd;
        return;
    }
    head = *cmds;
    while (head->next)
        head = head->next;
    head->next = cmd;
}

t_cmd	*new_cmd(int cmd_n, int red_n)
{
	t_cmd	*head;

	head = (t_cmd *)malloc(sizeof(t_cmd));
	if (!head)
		return (NULL);
	head->cmd = malloc(sizeof(char *) * (cmd_n + 1));
	if (!head->cmd)
	{
		free(head);
		return NULL;
	}
	head->red = malloc(sizeof(char *) * (red_n + 1));
	if (!head->red)
	{
		free(head);
		return NULL;
	}
	head->next = NULL;
	return (head);
}

void	del_one_cmd(t_cmd *cmds, void (*del)(void *))
{
	if (!cmds)
		return ;
	del(cmds->red);
	del(cmds->cmd);
	free(cmds);
}

void	clear_cmd(t_cmd **cmd, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		del_one_cmd(*cmd, del);
		*cmd = tmp;
	}
}
