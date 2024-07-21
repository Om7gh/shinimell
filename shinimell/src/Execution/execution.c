/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 09:42:00 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/21 20:48:33 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// ls -la,     wc -l,    grep -r

int     execution(t_minishell *mini, t_cmd *cmds)
{
        // if (between_pipe(mini->start) == 1 && !cmds->red[0])
	// {
	// 	if (ft_strcmp(mini->start->token, "exit") == 0)
	// 		ft_exit(mini->start->next);
	// 	else if (ft_strcmp(mini->start->token, "cd") == 0)
	// 		mini->ret_value = cd(mini->start->next, mini->env);
	// 	else if (ft_strcmp(mini->start->token, "export") == 0)
	// 		mini->ret_value = export(mini->start->next, mini->env);
	// 	else if (ft_strcmp(mini->start->token, "unset") == 0)
	// 		mini->ret_value = unset(mini->start->next, &mini->env);
	// 	else if (ft_strcmp(mini->start->token, "env") == 0)
	// 		mini->ret_value = env(mini->env);
	// 	else if (ft_strcmp(mini->start->token, "echo") == 0)
	// 		mini->ret_value = echo(mini->start->next);
	// 	else if (ft_strcmp(mini->start->token, "pwd") == 0)
	// 		mini->ret_value = pwd(mini->start);
        //         else
        //                 mini->ret_value = single_process(mini, cmds);
	// }
        if (node_len(cmds) == 1)
                return (single_process(mini, cmds));
        else
                return (multi_process(mini, cmds));
}

static int	envname_size(t_env *env)
{
	int	i;

	if (!env)
		return (0);
	i = 1;
	while (env->next)
	{
		if (env->key && env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**env_to_array(t_env *env_list)
{
	int		i;
	int		size;
	char	**env;

	if (!env_list)
		return (NULL);
	size = envname_size(env_list);
	env = malloc(sizeof(char *) * (size + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (env_list)
	{
		if (env_list->key && env_list->value)
		{
			*(env + i) = env_join(env_list->key, env_list->value);
			i++;
		}
		env_list = env_list->next;
	}
	return (*(env + i) = NULL, env);
}

int     my_execve(t_minishell *mini, t_cmd *cmds)
{
        int     i;
        char    *path;
        char    **my_env;

        i = 0;
        my_env = env_to_array(mini->env);
        if (cmds->cmd)
        {
                path = find_cmd(mini, cmds->cmd[0]);
                if (path)
                {
                        execve(path, cmds->cmd, my_env);
                        perror("execve");
                }
                else
                {
                        printf("minishell: %s: command not found\n", cmds->cmd[i]);
                        return (127);
                }
        }
        return (0);
}
