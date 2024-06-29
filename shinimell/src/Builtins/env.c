/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:54:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/29 15:55:03 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     env(t_minishell *mini, t_env *env)
{
        t_env *tmp;

        tmp = env;
        while (tmp)
        {
                if (tmp->value)
                        printf("%s=%s\n", tmp->key, tmp->value);
                else
                        printf("%s=\n", tmp->key);
                tmp = tmp->next;
        }
        return (mini->ret_value);
}
