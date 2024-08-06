/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:24 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/06 17:45:43 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     is_valid(char c)
{
        return (c == '+' || c == '-' || c == ' ' || c == '|' || c == '\t' || c == '>' || c == '<' || (c > '0' && c <= '9'));
}

int     check_exit_status(t_tokenizer *token)
{
        int     i;

        i = -1;
        while (token->token[++i])
        {
                if (!is_valid(token->token[i]))
                        return (ERROR);
        }
        return (SUCCESS);
}

int     ft_exit(t_tokenizer *token)
{
        int     res;
        int     flag;
        t_tokenizer *tmp;

        flag = 0;
        tmp = token;
        if (!token)
                exit(0);
        while (tmp)
        {
                if (!ft_strncmp(tmp->token, ">", 1) || !ft_strncmp(tmp->token, ">>", 1) || !ft_strncmp(tmp->token, "<", 1) \
                        || !ft_strncmp(tmp->token, "<<", 1) || !ft_strncmp(tmp->token, "|", 1))
                {
                        tmp = tmp->next->next;
                        continue;
                }
                if (check_exit_status(tmp) == ERROR)
                {
                        ft_putstr_fd("exit\nminishell: exit: ", 2);
                        ft_putstr_fd(tmp->token, 2);
                        ft_putstr_fd(": numeric argument required\n", 2);
                        exit(255);
                }
                if (!check_exit_status(tmp) && tmp->next && !check_exit_status(tmp->next))
                {
                       flag = 1;
                       break ;
                }
                tmp = tmp->next;
        }
        if (flag)
        {
                printf("exit\nminishell: exit: too many arguments\n");
                return (1);
        }
        res = ft_atoi(token->token);
        if (res < 0)
                exit(255 + res);
        else if (res > 0)
                exit(res);
        return (0);
}
