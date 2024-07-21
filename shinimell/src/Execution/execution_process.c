/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:04:21 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/21 20:53:33 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int     single_process(t_minishell *mini, t_cmd *cmds)
{
        pid_t   pid;
        int     status;

        pid = fork();
        if (pid == -1)
                return (perror("fork"), 1);
        if (pid == 0)
                mini->ret_value = my_execve(mini, cmds);
        waitpid(pid, &status, 0);
        return (mini->ret_value);
}

int     multi_process(t_minishell *mini, t_cmd *cmds)
{
        mini->in = dup(STDIN_FILENO);
        mini->out = dup(STDOUT_FILENO);
                
        return (mini->ret_value);
}
