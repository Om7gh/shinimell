/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_pro_max.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:23:13 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/10 23:33:13 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     ft_strcmp(char *s1, char *s2)
{
        int     i;

        i = 0;
        while (s1[i] || s2[i])
        {
                if (s1[i] != s2[i])
                        return (s1[i] - s2[i]);
                i++;
        }
        return (0);
}

int	between_pipe(t_tokenizer *lst)
{
	int		length;

	if (!lst)
		return (0);
	length = 1;
	while (lst)
	{
                if (*lst->type == PIPE)
                        length++;
		lst = lst->next;
	}
	return (length);
}
