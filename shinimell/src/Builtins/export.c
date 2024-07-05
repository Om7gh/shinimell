/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/05 20:53:42 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    join_nodes(t_tokenizer **token)
{
        t_tokenizer *tmp;

        tmp = *token;
        while (tmp->next)
        {
                if (*tmp->stat != *tmp->next->stat)
                {
                        tmp->token = ft_strjoin(tmp->token, tmp->next->token);
                        tmp->next = tmp->next->next;
                        if (tmp->next)
                                tmp->next->prev = tmp;
                }
                else
                        tmp = tmp->next;
        }
}

int     export(t_tokenizer *token, t_env *env)
{
        t_env   *tmp;
        int     flag;

        if (!token)
        {
                tmp = env;
                while (tmp)
                {
                        if (tmp->value)
                                printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
                        else
                                printf("declare -x %s\n", tmp->key);
                        tmp = tmp->next;
                }
                return (0);
        }
        if (ft_strchr(token->token, '+') && !ft_strchr(token->token, '='))
        {
                printf("%sexport: not valid in this context: %s\n%s", YELLOW_COLOR, token->token, RESET);
                return (1);
        }
        if (token)
        {
                join_nodes(&token);
                while (token)
                {
                        if (!ft_strchr(token->token, '=') && !ft_strchr(token->token, '+'))
                        {
                                tmp = env;
                                flag = 0;
                                while (tmp)
                                {
                                        if (!ft_strcmp(token->token, tmp->key))
                                        {
                                                flag = 1;
                                                break ;
                                        }
                                        tmp = tmp->next;
                                }
                                if (!flag)
                                {
                                        tmp = new_env(ft_strdup(token->token), NULL);
                                        append_env(&env, tmp);
                                }
                        }
                        else if (ft_strchr(token->token, '=') && !ft_strchr(token->token, '+'))
                        {
                                flag = 0;
                                tmp = env;
                                while (tmp)
                                {
                                        if (!ft_strcmp(ft_split(token->token, '=')[0], tmp->key))
                                        {
                                                flag = 1;
                                                break ;
                                        }
                                        tmp = tmp->next;
                                }
                                if (!tmp)
                                        flag = 0;
                                if (flag)
                                {
                                        if (ft_strchr(token->token, '=') && ft_strchr(token->token, '='))
                                                tmp->value = ft_strdup(ft_strchr(token->token, '='));
                                        else
                                        {
                                                tmp->value = NULL;
                                                tmp->key = ft_strdup(token->token);
                                        }
                                }
                                else
                                {
                                        tmp = new_env(ft_split(token->token, '=')[0], ft_strdup(ft_strchr(token->token, '=') + 1));
                                        printf("%s\t%s\n", tmp->key, tmp->value);
                                        append_env(&env, tmp);
                                }
                        }
                        else if (ft_strchr(token->token, '+'))
                        {
                                flag = 0;
                                tmp = env;
                                while (tmp)
                                {
                                        if (!ft_strcmp(ft_split(token->token, '+')[0], tmp->key))
                                        {
                                                flag = 1;
                                                break ;
                                        }
                                        tmp = tmp->next;
                                }
                                if (!tmp)
                                        flag = 0;
                                if (flag)
                                {
                                        if (ft_strchr(token->token, '+') && ft_strchr(token->token, '+'))
                                                tmp->value = ft_strjoin(tmp->value, ft_strpbrk(token->token, "+=") + 2);
                                        else
                                        {
                                                tmp->value = NULL;
                                                tmp->key = ft_strdup(token->token);
                                        }
                                }
                                else
                                {
                                        tmp = new_env(ft_split(token->token, '+')[0], ft_strchr(token->token, '+') + 1);
                                        append_env(&env, tmp);
                                }
                        }
                        token = token->next;
                }
        }
        return (0);
}
