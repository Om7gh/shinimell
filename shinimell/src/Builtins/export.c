/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/02 15:03:25 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     export(t_tokenizer *token, t_env *env)
{
        t_env *tmp;
        int flag;

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
                while (token)
                {
                        if (!ft_strchr(token->token, '=') && !ft_strchr(token->token, '+'))
                        {
                                tmp = new_env(ft_strdup(token->token), NULL);
                                append_env(&env, tmp);
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
                                        if (ft_strchr(token->token, '=') && ft_split(token->token, '=')[1])
                                                tmp->value = ft_strdup(ft_split(token->token, '=')[1]);
                                        else
                                        {
                                                tmp->value = NULL;
                                                tmp->key = ft_strdup(token->token);
                                        }
                                }
                                else
                                {
                                        tmp = new_env(ft_split(token->token, '=')[0], ft_split(token->token, '=')[1]);
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
                                        if (ft_strchr(token->token, '+') && ft_split(token->token, '+')[1])
                                                tmp->value = ft_strjoin(tmp->value, ft_strpbrk(token->token, "+=") + 2);
                                        else
                                        {
                                                tmp->value = NULL;
                                                tmp->key = ft_strdup(token->token);
                                        }
                                }
                                else
                                {
                                        tmp = new_env(ft_split(token->token, '+')[0], ft_split(token->token, '+')[1]);
                                        append_env(&env, tmp);
                                }
                        }
                        token = token->next;
                }
        }
        return (0);
}

/*
        $PWD
*/