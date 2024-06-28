/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:35:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/28 21:46:50 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special(int c)
{
	return (c == '|' || c == '>' || c == '<' || c == ' ' || \
		c == '"' || c == '\'');
}

t_cmd	*send_to_execution(t_tokenizer *token)
{
	t_tokenizer	*head;	
	t_cmd		*cmd;
	t_cmd		*node;
	int		cmd_len;
	int		redirection_len;

	head = token;
	while (head)
	{
		while (head && *head->type != PIPE)
		{
			if (*head->type == WORD)
			{
				node = new_cmd(&head->token, NULL);
				if (!node)
					return (NULL);
				append_to_exec(&cmd, node);
			}
			else if (*head->type == LESS || *head->type == GREAT \
					|| *head->type == LESSLESS || *head->type == GREATGREAT)
			{
				node = new_cmd(NULL, &head->token);
				if (!node)
					return (NULL);
				append_to_exec(&cmd, node);
			}
			head = head->next;
		}
		head = head->next;
	}	
}
