/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/02 15:10:24 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     unset(t_tokenizer *token, t_env *env)
{
        t_env *tmp;
        t_env *prev;
        int flag;

        if (!token)
                return (0);
        while (token)
        {
                tmp = env;
                prev = env;
                flag = 0;
                while (tmp)
                {
                        if (!ft_strcmp(token->token, tmp->key))
                        {
                                if (tmp == env)
                                        env = env->next;
                                else
                                        prev->next = tmp->next;
                                flag = 1;
                                break ;
                        }
                        prev = tmp;
                        tmp = tmp->next;
                }
                if (!flag)
                        return (0);
                token = token->next;
        }
        return (0);
}
