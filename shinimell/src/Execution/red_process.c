/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:49:32 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/24 22:36:47 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int send_redir(t_cmd *cmds)
{
        int     fd;

        if (cmds && cmds->red && cmds->red[1])
        {
                fd = open(cmds->red[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                        perror("open");
                dup2(fd, STDOUT_FILENO);
                close(fd);
        }
        return (0);
}

int read_redir(t_cmd *cmds)
{
        int     fd;

        fd = open(cmds->red[1], O_RDONLY, 0644);
        if (fd < 0)
                perror("open");
        dup2(fd, STDIN_FILENO);
        close(fd);
        return (0);
}

int append_redir(t_cmd *cmds)
{
        int     fd;

        fd = open(cmds->red[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
                perror("open");
        dup2(fd, STDOUT_FILENO);
        close(fd);
        return (0);
}

int     heredoc(t_minishell *mini)
{
        dup2(mini->infile, STDIN_FILENO);
        close(mini->infile);
        return (0);
}

int red_process(t_minishell *mini, t_cmd *cmds)
{
        int     i;
        t_cmd   *tmp;

        i = 0;
        tmp = cmds;
        while (tmp)
        {
                if (!ft_strcmp(tmp->red[0], "<"))
                        i = read_redir(tmp);
                else if (!ft_strcmp(tmp->red[0] , ">"))
                        i = send_redir( tmp);
                else if (!ft_strcmp(tmp->red[0], ">>"))
                        i = append_redir(tmp);
                else if (!ft_strcmp(tmp->red[0], "<<"))
                        i = heredoc(mini);
                tmp = tmp->next;
                if (i < 0)
                        return (-1);
        }
        return (0);
}
