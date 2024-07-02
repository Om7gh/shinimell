/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:47:01 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/30 18:58:46 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     unset(t_tokenizer *token, t_env *env)
{
       t_env *head;
       t_env *tmp;

        if (!token)
                return (0);
        head = env;
        while (token)
        {
                tmp = head;
                while (head)
                {
                        if (!ft_strcmp(head->key, token->token))
                        {
                                head->value = NULL;
                                head->key = NULL;
                                return (0);
                        }
                        head = head->next;
                }
                token = token->next;
        }
        return (0);
}
