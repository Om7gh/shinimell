/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:21:47 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/12 08:55:43 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_tokenizer	*lexer;
	t_env		*envr;

	(void)argc;
	(void)argv;
	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
	{
		printf("%serror with malloc%s\n", RED_COLOR, RESET);
		exit(ERROR);
	}
	store_env(env, &envr);
	minishell->in = dup(0);
	minishell->out = dup(1);
	minishell->exit = 0;
	minishell->no_exec = 0;
	minishell->ret_value = 0;
	minishell->env = envr;
	minishell->is_builting = 0;
	while (minishell->exit == 0)
	{
		minishell->line = readline("\x1b[32mminishell-1.0$\x1b[0m :");
		if (!minishell->line)
			return (minishell->ret_value);
		lexer_first(&lexer, minishell->line);
		minishell->start = lexer;
		parse_input(minishell);
		close(minishell->cmd->infile);
		unlink("/tmp/.ana_machi_heredoc");
		if (minishell->line)
			add_history(minishell->line);
		free(minishell->line);
		clear_token(&lexer, free);
	}
	close(minishell->in);
	close(minishell->out);
	free(minishell->line);
	free(minishell);
	minishell = NULL;
	return (minishell->ret_value);
}
