/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:41 by omghazi           #+#    #+#             */
/*   Updated: 2024/07/28 20:40:32 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_tokenizer    *check_args(t_tokenizer *token, int *count)
{
       int    i;

       while (token)
       {
              i = 1;
              if (token->token[0] == '-')
              {
                     while (token->token[i] == 'n')
                            i++;
                     if (token->token[i] != '\0')
                            return (token);
                     (*count)++;
              }
              else
                     return (token);
              token = token->next;
       }
       return (NULL);
}

int     echo(t_tokenizer *token)
{
       int    i;

       i = 0;
       token = check_args(token, &i);
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
       if (!i)
              printf("\n");
       return (0);
}
