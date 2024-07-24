/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/23 20:29:18 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     echo(t_tokenizer *token)
{
       if (token && ft_strcmp(token->token, "-n") == 0)
       {
              if (token->next)
                     token = token->next;
              while (token)
              {
                     if (!ft_strcmp(token->token, ">") || !ft_strcmp(token->token, ">>") || !ft_strcmp(token->token, "<") || !ft_strcmp(token->token, "<<"))
                     {
                            token = token->next;
                            if (token->next)
                                   token = token->next->next;
                     }
                     printf("%s", token->token);
                     token = token->next;
                     if (token)
                            printf(" ");
              }
       }
       else
       {
              while (token)
              {
                     if (!ft_strncmp(token->token, ">", 1) || !ft_strncmp(token->token, ">>", 2) || !ft_strncmp(token->token, "<", 1) || !ft_strncmp(token->token, "<<", 2))
                            token = token->next->next;
                     if (token)
                     {
                            printf("%s", token->token);
                            token = token->next;
                     }
                     if (token)
                            printf(" ");
              }
              printf("\n");
       }
       return (0);
}
