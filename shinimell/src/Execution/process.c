/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:49:20 by omghazi           #+#    #+#             */
/*   Updated: 2024/08/01 16:41:11 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int process(t_minishell *mini, t_cmd *cmds, int input, int output)
{
        
        if (input != STDIN_FILENO && dup2(input, 0) < 0)
                return (1);
        if (output != STDOUT_FILENO)
                close(output);
        if (output != STDOUT_FILENO &&  dup2(output, 1) < 0)
                return (1);
        if (input != STDIN_FILENO)
                close(input);
        if (is_builtins(cmds))
                return (execute_builtin(mini, cmds));
        else
                return (my_execve(mini, cmds));
}
