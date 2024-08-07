/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/06 22:53:41 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	word_char(char c)
{
	return (c == '_' || c == '$');
}

int	check_validation(t_tokenizer *token, t_minishell *mini)
{
	if (token && *token->type == PIPE)
		return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
	while (token)
	{
		if (token && *token->type != WORD && !token->next)
			return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		if (*token->type == LESSLESS && *token->next->type == WORD)
			if (!here_doc(token->next, mini))
				return (0);
		if (*token->type != WORD)
		{
			if (token->next)
				if (*token->next->type == PIPE)
					return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		}
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
}

void	remove_quotes(t_tokenizer *token)
{
	t_tokenizer	*tmp;
	char		*str;
	int		i;

	str = NULL;
	tmp = token;
	while (tmp)
	{
		i = 0;
		if (*tmp->stat == INDQUOTES)
		{
			while (tmp->token[i])
			{
				if (tmp->token[i] != '"')
					str = ft_strjoin(str, ft_substr(tmp->token, i, i + 1));
				if (tmp->token[i])
					i++;
			}
			tmp->token = ft_strdup(str);
		}
		else if (*tmp->stat == INQUOTES)
		{
			while (tmp->token[i])
			{
				if (tmp->token[i] != '\'')
					str = ft_strjoin(str, ft_substr(tmp->token, i, i + 1));
				if (tmp->token[i])
					i++;
			}
			tmp->token = ft_strdup(str);
		}
		tmp = tmp->next;
	}
}

// void print_commande(t_cmd *cmds)
// {
// 	for (t_cmd *head = cmds; head; head = head->next)
// 	{
// 		for (int i = 0; head->cmd[i]; i++)
// 			printf("cmd[%d]: %s\n", i, head->cmd[i]);
// 		for (int i = 0; head->red[i]; i++)
// 			printf("red[%d]: %s\n", i, head->red[i]);
// 		printf("------------\n");
// 	}
// }

void print_commande(t_cmd *cmds)
{
	for (t_cmd *head = cmds; head; head = head->next)
	{
		for (int i = 0; head->cmd[i]; i++)
			printf("cmd[%d]: %s\n", i, head->cmd[i]);
		printf("------------\n");
	}
}

void	parse_input(t_minishell *mini, t_cmd **cmds)
{
	remove_quotes(mini->start);
	if (!check_validation(mini->start, mini))
		return ;
	if (mini->start)
	{
		send_to_execution(mini->start, cmds);
		mini->cmd = *cmds;
		mini->ret_value = execution(mini, *cmds);
	}
}
