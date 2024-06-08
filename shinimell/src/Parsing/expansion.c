/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:23:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/06 16:42:51 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_value(t_minishell **mini, char *key)
{
	t_env	*envr;

	envr = (*mini)->env;
	while (envr)
	{
		if (!strncmp(envr->key, key, ft_strlen(key)))
			return (envr->value);
		envr = envr->next;
	}
	return (ft_strdup(""));
}

void	expansion(t_tokenizer *token, t_minishell *mini)
{
	char	*join_it;
	char	*str;
	int	i;
	int	j;
	int	count;
	
	i = 0;
	str = NULL;
	join_it = 0;
	j = 0;
	while (token->token[i])
	{
		count = 0;
		if (token->token[i] == '$')
		{
			while (token->token[i] == '$' && token->token[i + 1] == '$')
				(count++, i++);
			if (count % 2 == 0)
			{
				i++;
				j = i;
				while (ft_isalnum(token->token[i]) || token->token[i] == '_' || ft_isalpha(token->token[i]))
					i++;
				str = get_value(&mini, ft_substr(token->token, j, i));
				join_it = ft_strjoin(join_it, str);
			}
			else
			{
				j = i;
				while (token->token[i] && token->token[i] != ' ')
					i++;
				str = ft_substr(token->token, j - count, i);
				join_it = ft_strjoin(join_it, str);
			}
		}
		else
		{
			j = i;
			while (ft_isalnum(token->token[i]) || ft_isalpha(token->token[i]) || token->token[i] == '_' || token->token[i] == ' ')
				i++;
			str = ft_substr(token->token, j, i);
			join_it = ft_strjoin(join_it, str);
		}
	}
	token->token = ft_strdup(join_it);
	token->len = ft_strlen(join_it);
	*token->type = WORD;
}

// $$$$$$$$$$$$$$$USER
/*
case to check
	'$USER'
	$$USER
	$USER
	"$USER"
	"'$USER'"
	"$$$$USER"
*/
