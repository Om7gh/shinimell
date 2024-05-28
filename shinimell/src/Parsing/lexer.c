/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 05:59:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/28 11:29:37 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat)
{
	t_tokenizer	*node;
	char		*s;

	s = ft_substr(input, *j, *j + 1);
	node = new_token(s, &type[0], stat);
	return (node);
}

t_tokenizer	*token_word(char *input, t_lexer *type, t_stat *stat, int *i)
{
	t_tokenizer	*node;
	int			j;
	char		*s;

	j = 0;
	while (input[*i] && (!is_special(input[*i]) && !ft_isspace(input[*i])))
	{
		j++;
		(*i)++;
	}
	s = ft_substr(input, *i - j, *i);
	node = new_token(s, type, stat);
	return (node);
}

t_tokenizer	*token_special_char(char *input, t_lexer *type, t_stat *stat, \
		int *i)
{
	t_tokenizer	*node;
	char		*s;
	int			j;

	node = NULL;
	s = NULL;
	j = *i;
	if (input[*i] && input[*i] == '|')
		node = make_node(input, i, &type[1], &stat[0]);
	else if (input[*i] && input[*i] == '"')
		node = check_double_quotes(input, i, type, stat);
	else if (input[*i] && input[*i] == '\'')
		node = check_signle_quotes(input, i, type, stat);
	else if (input[*i] && input[*i] == '>' && input[*i + 1] == '>')
	{
		s = ft_substr(input, j, j + 2);
		node = new_token(s, &type[5], &stat[0]);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '>' && input[*i + 1] != '>')
		node = make_node(input, &j, &type[4], &stat[0]);
	else if (input[*i] && input[*i] == '<' && input[*i + 1] == '<')
	{
		s = ft_substr(input, j, j + 2);
		node = new_token(s, &type[7], &stat[0]);
		(*i)++;
	}
	else if (input[*i] && input[*i] == '<' && input[*i + 1] != '<')
		node = make_node(input, &j, &type[6], &stat[0]);
	else if (input[*i] && input[*i] == ' ')
		node = make_node(input, &j, &type[3], &stat[0]);
	(*i)++;
	return (node);
}

void	lexer_first(t_tokenizer **token, char *input)
{
	t_tokenizer	*node;
	int			i;
	t_stat		stat[3];
	t_lexer		type[10];

	stat[0] = GENERAL;
	stat[1] = INQUOTES;
	stat[2] = INDQUOTES;
	type[0] = WORD;
	type[1] = PIPE;
	type[2] = DOLLAR;
	type[3] = WHITESPACE;
	type[4] = GREAT;
	type[5] = GREATGREAT;
	type[6] = LESS;
	type[7] = LESSLESS;
	type[8] = QUOTE;
	type[9] = D_QUOTE;
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			continue ;
		}
		if (input[i] && !is_special(input[i]) && !ft_isspace(input[i]))
			node = token_word(input, type, stat, &i);
		else if (input[i] && is_special(input[i]))
			node = token_special_char(input, type, stat, &i);
		if (!node)
			return (clear_token(token, free));
		append_token(token, node);
	}
}
