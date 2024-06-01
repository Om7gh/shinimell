/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/01 15:53:49 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_validation(t_tokenizer *token)
{
	if (*token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
	while (token)
	{
		if (*token->type != WORD && !token->next)
			return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		if (*token->type != WORD && *token->next->type != WORD)
			return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		if (ft_strchr(token->token, '$') && *token->stat == INDQUOTES)
			expansion(&token);
		token = token->next;
	}
	return (1);
}

void	parse_input(t_minishell *mini)
{
	t_tokenizer	*token;

	token = mini->start;
	if (!check_validation(token))
		return ;
	// print_token(token);
}
