/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:00:29 by omghazi           #+#    #+#             */
/*   Updated: 2024/05/28 10:18:14 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_tokenizer	*token)
{
	while (token)
	{
		printf("token\t[%s]\n", token->token);
		token = token->next;
	}
}
