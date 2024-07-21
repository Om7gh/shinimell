/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:20:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/21 18:05:14 by omghazi          ###   ########.fr       */
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

       path = find_path(mini);
       full_path = ft_strjoin("/", cmd); // /ls
        if (!path)
                 return (NULL);
        while (*path)
        {
                cmd = ft_strjoin(*path, full_path);
                if (!access(cmd, X_OK))
                        return (cmd);
                path++;
        }
        return (NULL);
}

char    *find_cmd(t_minishell *mini, char *cmd)
{
        char    *path;

        path = join_cmd_path(mini, cmd);
        if (path)
                return (path);
        return (NULL);
}
