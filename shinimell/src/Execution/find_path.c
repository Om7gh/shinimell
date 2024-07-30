/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:20:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/26 18:51:44 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char        **find_path(t_minishell *env)
{
        t_env   *tmp;

        tmp = env->env;
        while (tmp)
        {
                if (!ft_strncmp(tmp->key, "PATH", 4))
                        return (ft_split(tmp->value, ':'));
                tmp = tmp->next;
        }
        return (NULL);
}

char    *join_cmd_path(t_minishell *mini, char *cmd)
{
       char     **path;
       char     *full_path;
       struct   stat file;

       path = find_path(mini);
        if (!path)
                 return (NULL);
        if (stat(cmd, &file) == 0 && S_ISDIR(file.st_mode))
        {
                write(2 , "minishell: ", 11);
                write(2 , cmd, ft_strlen(cmd));
                write(2 ," is a directory\n", 16);
                exit(126);
        }
        if (!access(cmd, F_OK) || !access(cmd, X_OK))
                return (cmd);
        else
        {
                full_path = ft_strjoin("/", cmd);
                while (*path)
                {
                        cmd = ft_strjoin(*path, full_path);
                        if (!access(cmd, F_OK) || !access(cmd, X_OK))
                                return (cmd);
                        path++;
                }
                return (NULL);
        }
}

char    *find_cmd(t_minishell *mini, char *cmd)
{
        char    *path;

        path = join_cmd_path(mini, cmd);
        if (path)
                return (path);
        return (NULL);
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
                        exit(1);
                }
                else
                {
                        printf("minishell: %s: command not found\n", cmds->cmd[i]);
                        exit(127);
                }
        }
        return (0);
}
