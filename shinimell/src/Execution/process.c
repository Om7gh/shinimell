/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:20 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/03 14:36:00 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int process(t_minishell *mini, t_cmd *cmds, int input, int output)
{
        if (red_process(mini, cmds) == -1)
                exit(1);
        if (input != STDIN_FILENO && dup2(input, 0) < 0)
                exit (1);
        if (output != STDOUT_FILENO &&  dup2(output, 1) < 0)
                exit (1);
        if (is_builtins(cmds))
                return (execute_builtin(mini, cmds));
        else
                return (my_execve(mini, cmds));
}
