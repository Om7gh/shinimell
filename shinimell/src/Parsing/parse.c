/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/08 11:28:45 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
	while (token)
	{
		if (*token->type != WORD && !token->next)
			return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		if (*token->type == LESSLESS)
			if (!here_doc(token, token->next, mini))
				return (0);
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			expansion(token, mini);
		token = token->next;
	}
	return (1);
}

void	parse_input(t_minishell *mini)
{
	t_cmd *cmds;
	
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return ;
	cmds->infile = open("/tmp/.ana_machi_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	mini->cmd = cmds;
	if (!check_validation(mini->start, mini))
		return ;
	send_to_execution(mini->start, mini, cmds);
}
