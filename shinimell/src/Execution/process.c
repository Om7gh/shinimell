#include <minishell.h>

static char	**cmd_executable(t_cmd *cmds)
{
	char	**new;
	t_cmd	*tmp;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (node_len(cmds) + 1));
	tmp = cmds;
	while (tmp)
	{
		if (tmp->cmd[i])
		{
			new[i] = ft_strdup(tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
	new[i] = NULL;
	return (new);
}

int process(t_minishell *mini, t_cmd *cmd)
{
	char	**get_cmds;

	get_cmds = cmd_executable(cmd);
	if (!get_cmds)
		exit(1);

	mini->ret_value = execution(mini, cmd);
	return (0);
}
