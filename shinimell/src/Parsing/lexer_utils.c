/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:20:23 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/28 11:32:51 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;

	if (input[*i] == '\'')
	{	
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'' && input[*i] != '\0')
		{
			puts("hello");
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
			return (node);
		}
		else
			return (printf("error with single quotes\n"), NULL);
	}
	return (printf("error with single quotes\n"), NULL);
}

t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat)
{
	t_tokenizer	*node;
	int			k;
	char		*s;

	if (input[*i] == '"')
	{	
		(*i)++;
		k = *i;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"' && input[*i] != '\0')
		{
			puts("hello");
			s = ft_substr(input, k, *i);
			node = new_token(s, type, stat);
			return (node);
		}
		else
			return (printf("error with double quotes\n"), NULL);
	}
	return (printf("error with double quotes\n"), NULL);
}

void	print_type(t_lexer lexer)
{
	if (lexer == WORD)
		printf("type : WORD\t\t");
	else if (lexer == WHITESPACE)
		printf("type : WHITESPACE\t\t");
	else if (lexer == D_QUOTE)
		printf("type : D_QUOTE\t\t");
	else if (lexer == QUOTE)
		printf("type : QUOTE\t\t");
	else if (lexer == PIPE)
		printf("type : PIPE\t\t");
	else if (lexer == LESS)
		printf("type : LESS\t\t");
	else if (lexer == LESSLESS)
		printf("type : LESSLESS\t\t");
	else if (lexer == GREAT)
		printf("type : GREATER\t\t");
	else if (lexer == GREATGREAT)
		printf("type : GREATER_GREATER\t\t");
	else
		printf("NO TYPE\t\t");
}

void	print_state(t_stat stat)
{
	if (stat == GENERAL)
		printf("type GENERAL\n");
	else if (stat == INQUOTES)
		printf("type INQUOTES\n");
	else if (stat == INDQUOTES)
		printf("type INDQUOTES\n");
	else
		printf("NO STAT\n");
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}
