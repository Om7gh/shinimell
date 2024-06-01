/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:23:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/01 15:54:55 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	store_env(t_list **env_list, char **env)
{
	t_list	*node;
	int		i;

	node = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_lstnew(env[i]);
		if (node == NULL)
			return (printf("error with malloc\n"), 0);
		ft_lstadd_back(env_list, node);
		i++;
	}
	return (1);
}

char    *get_variable(t_minishell **mini, char *key)
{
        t_list  *env;

        env = (*mini)->env;
        while (env)
        {
                if (!ft_strncmp(env->content, key, ft_strlen(key)))
                        return (env->content);
                env = env->next;
        }
        return (NULL);
}

void    expansion(t_tokenizer **token)
{
	t_tokenizer *head;
	
	head = *token;
	
}

/*
case to check
	'$USER'
	$$USER
	$USER
	"$USER"
	"'$USER'"
	"$$$$USER"
*/
