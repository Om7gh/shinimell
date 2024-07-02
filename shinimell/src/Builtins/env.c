/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:54:45 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/30 10:44:12 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     env(t_env *env)
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
        return (0);
}
