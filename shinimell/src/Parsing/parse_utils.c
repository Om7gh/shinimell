/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/12 08:51:38 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == ' ' || \
		c == '"' || c == '\'');
}

void	how_much(t_tokenizer **token, int *cmds_number, int *red_number)
{
	while (*token && *(*token)->type != PIPE)
	{
		if (*token && *(*token)->type != WORD)
		{
			*red_number += 2;
			*token = (*token)->next->next;
			continue;
		}
		(*cmds_number)++;
		*token = (*token)->next;
	}
}

static int	allocate_for_exec(t_tokenizer **token, t_cmd **cmd)
{
	int	cmds_number;
	int	red_number;
	int	i;
	int	size;
	t_tokenizer	*head;

	i = 0;
	size = between_pipe(*token);
	(*cmd)->cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!(*cmd)->cmd)
		return (0);
	(*cmd)->red = (char **)malloc(sizeof(char *) * (size + 1));
	if (!(*cmd)->red)
		return (0);
	head = *token;
	while (head)
	{
		red_number = 0;
		cmds_number = 0;
		how_much(&head, &cmds_number, &red_number);
		(*cmd)->cmd[i++] = (char *)malloc(sizeof(char) * (cmds_number + 1));
		(*cmd)->red[i++] = (char *)malloc(sizeof(char) * (red_number + 1));
		if (head && head->next)
			head = head->next;
	}
	return (1);
}

void	send_to_execution(t_tokenizer *token, t_cmd **cmd)
{
	int	i;
	t_cmd	*node;

	i = 0;
	allocate_for_exec(&token, cmd);
	while (token)
	{
		if (*token->type != WORD)
		{
			node = new_cmd(NULL, &token->token, token->type);
			if (!node)
			{
				printf("error with malloc");
				return ;
			}
			append_to_exec(cmd, node);
		}
		else
		{
			node = new_cmd(&token->token, NULL, token->type);
			if (!node)
			{
				printf("error with malloc");
				return ;
			}
			append_to_exec(cmd, node);
		}
		if (token && token->next)
			token = token->next;
	}
}
