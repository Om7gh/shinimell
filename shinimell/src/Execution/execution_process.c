/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:04:21 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/23 15:44:12 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     single_process(t_minishell *mini, t_cmd *cmds)
{
        int     status;

        mini->fdin = dup(STDIN_FILENO);
        mini->fdout = dup(STDOUT_FILENO);
        if (cmds->red && cmds->red[0])
                if (red_process(mini, cmds))
                        return (1);
        status = execute_single_commande(mini, cmds);
        dup2(mini->fdin, STDIN_FILENO);
        dup2(mini->fdout, STDOUT_FILENO);
        return (status);
}

int     execute_single_commande(t_minishell *mini, t_cmd *cmd)
{
        pid_t   pid;
        int     status;

        status = 0;
        if (is_builtins(cmd))
                mini->ret_value = execute_builtin(mini, cmd);
        else
        {
                pid = fork();
                if (pid == -1)
                        return (perror("fork"), 1);
                if (pid == 0)
                        status = my_execve(mini, cmd);
                waitpid(pid, &status, 0);
        }
        return (status);
}

int     execute_builtin(t_minishell *mini, t_cmd *cmd)
{
                if (!ft_strncmp(cmd->cmd[0], "export", 6))
                         return (export(mini->start->next, mini->env));
                if (!ft_strncmp(cmd->cmd[0], "unset", 5))
                        return (unset(mini->start->next, &mini->env));
                if (!ft_strncmp(cmd->cmd[0], "env", 3))
                        return (env(mini->env));
                if (!ft_strncmp(cmd->cmd[0], "exit", 4))
                        return (ft_exit(mini->start->next));
                if (!ft_strncmp(cmd->cmd[0], "cd", 2))
                        return (cd(mini->start->next, mini->env));
                if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
                        return (pwd(mini->start));
                if (!ft_strncmp(cmd->cmd[0], "echo", 4))
                        return (echo(mini->start->next));
        return (0);
}

int     multi_process(t_minishell *mini, t_cmd *cmds)
{
        (void)cmds;
        mini->in = dup(STDIN_FILENO);
        mini->out = dup(STDOUT_FILENO);

        return (mini->ret_value);
}
