/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:27:41 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/24 13:29:07 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	struct_init(t_cmd *cmd, char **envp)
{
	cmd->envp = envp;
	cmd->ats = NULL;
	cmd->fdp = NULL;
	cmd->pid_info.pid = NULL;
	cmd->pid_info.pipe_i = 0;
}

void	command_set(char *line, char **envp, t_env *env)
{
	t_token		*token;
	t_cmd		*command;
	bool		here_doc_check;

	token = NULL;
	command = (t_cmd *)malloc(sizeof(t_cmd));
	struct_init(command, envp);
	token = tokenize(line);
	if (!syntax_check(token))
		return (free(command));
	expansion(token, env);
	here_doc_check = redirect_open(token, env);
	command->ats = parser(token);
	if (here_doc_check)
		make_wait_child(command, env);
	free_token(token);
	free_command(command);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env;

	register_signal();
	rl_outstream = stderr;
	env = NULL;
	env = init_env(envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_eof(line);
		else
		{
			add_history(line);
			command_set(line, envp, env);
			free(line);
		}
	}
	(void)argc;
	(void)argv;
	return (0);
}
