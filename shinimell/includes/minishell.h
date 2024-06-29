/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omghazi <omghazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:22:53 by omghazi           #+#    #+#             */
/*   Updated: 2024/06/29 15:42:49 by omghazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <types.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>

/* FUNCTIONS */
int		pwd(t_minishell *mini);
int		export(t_minishell *mini, t_env *env);
int		exit(t_minishell *mini);
int		echo(t_minishell *mini);
int		cd(t_minishell *mini, t_env *env);
int		unset(t_minishell *mini, t_env *env);
void	send_to_execution(t_tokenizer *token, t_cmd **cmd);
void    count_len(t_tokenizer *lst, int *commands_len, int *redirection_len);
void	clear_cmd(t_cmd **cmd, void (*del)(void *));
void	del_one_cmd(t_cmd *cmds, void (*del)(void *));
t_cmd	*new_cmd(int cmd_n, int red_n);
void	append_to_exec(t_cmd **cmds, t_cmd *cmd);
int	between_pipe(t_tokenizer *lst);
int     ft_strcmp(char *s1, char *s2);
int 	here_doc(t_tokenizer *delimiter, t_minishell *mini);
char	*expansion(char *token, t_minishell *mini);
int     store_env(char **envr, t_env **env);
void	print_state(t_stat stat);
void	print_type(t_lexer lexer);
t_tokenizer	*check_signle_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat);
t_tokenizer	*check_double_quotes(char *input, int *i, t_lexer *type, \
		t_stat *stat);
t_tokenizer	*make_node(char *input, int *j, t_lexer *type, t_stat *stat);
t_tokenizer	*new_token(void *content, t_lexer *type, t_stat *stat);
void		print_token(t_tokenizer *token);
void		print_state(t_stat stat);
void		print_type(t_lexer lexer);
void		del_one_token(t_tokenizer *lst, void (*del)(void *));
void		clear_token(t_tokenizer **lst, void (*del)(void *));
void		lexer_first(t_tokenizer **token, char *input);
void		parse_input(t_minishell *mini, t_cmd **cmds);
void		append_token(t_tokenizer **tokens, t_tokenizer *token);
int			ft_isspace(char c);
int			is_special(int c);
