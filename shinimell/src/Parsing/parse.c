/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 07:55:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/30 10:44:32 by omghazi          ###   ########.fr       */
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
		if (*token->type == LESSLESS)
			if (!here_doc(token->next, mini))
				return (0);
		if (*token->type != WORD && *token->next->type != WORD)
			return (printf("syntax error near unexpected token `%s'\n", token->token), 0);
		if (ft_strchr(token->token, '$') && *token->stat != INQUOTES)
			token->token = expansion(token->token, mini);
		token = token->next;
	}
	return (1);
}

void	parse_input(t_minishell *mini, t_cmd **cmds)
{
	mini->infile = open("/tmp/.ana_machi_heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!check_validation(mini->start, mini))
		return ;
	if (ft_strcmp(mini->start->token, "exit") == 0)
		ft_exit(mini->start->next);
	else if (ft_strcmp(mini->start->token, "cd") == 0)
		mini->ret_value = cd(mini->start->next, mini->env);
	else if (ft_strcmp(mini->start->token, "export") == 0)
		mini->ret_value = export(mini->start->next, mini->env);
	else if (ft_strcmp(mini->start->token, "unset") == 0)
		mini->ret_value = unset(mini->start->next, mini->env);
	else if (ft_strcmp(mini->start->token, "env") == 0)
		mini->ret_value = env(mini->env);
	else if (ft_strcmp(mini->start->token, "echo") == 0)
		mini->ret_value = echo(mini->start->next);
	else if (ft_strcmp(mini->start->token, "pwd") == 0)
		mini->ret_value = pwd(mini->start, mini->env);
	else
		send_to_execution(mini->start, cmds);
	//print_token(mini->start);
}
