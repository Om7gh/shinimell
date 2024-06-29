/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:46:51 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/29 20:41:12 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     pwd(t_tokenizer *token, t_env *env)
{
        (void)env;
      char* path;

      path = token->token;
      path = getcwd(NULL, 0);
      if (!path)
      {
        printf("%spwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n%s", RED_COLOR, RESET);
        return (1);
      }
      printf("%s\n", path);
      return (0);
}
