
#include "minishell.h"

bool	builtin_check(t_token *token)
{
	while (token)
	{
		if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "exit", 4))
			return (true);
		else if (ft_strlen(token->str) == 2 && !ft_strncmp(token->str, "cd", 3))
			return (true);
		else if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "echo", 5))
			return (true);
		else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "pwd", 4))
			return (true);
		// export
		else if (ft_strlen(token->str) == 6 && !ft_strncmp(token->str, "export", 7))
			return (true);
		// env
		else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "env", 4))
			return (true);
		token = token->next;
	}
	return (false);
}

bool	builtin_control(t_token *token)
{
	t_token	*tmp;

	if (!builtin_check(token))
		return (false);
	tmp = token;
	while (tmp)
	{
		while (tmp && tmp->type == WORD)
			tmp = tmp->next;
		redirect(&tmp);
	}
	while (token)
	{
		if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "exit", 4))
			return(builtin_exit(token));
		else if (ft_strlen(token->str) == 2 && !ft_strncmp(token->str, "cd", 3))
			return(builtin_cd(token));
		else if (ft_strlen(token->str) == 4 && !ft_strncmp(token->str, "echo", 5))
			return(builtin_echo(token));
		else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "pwd", 4))
			return(builtin_pwd(token));
		// export
		else if (ft_strlen(token->str) == 6 && !ft_strncmp(token->str, "export", 7))
			return(builtin_export(token));
		// env
		else if (ft_strlen(token->str) == 3 && !ft_strncmp(token->str, "env", 4))
			return(builtin_env(token));
		token = token->next;
	}
	return (true);
}

		// if (ats->token->type == WORD && ft_strlen(ats->token->str) == 2 && !ft_strncmp(ats->token->str, "cd", 3))
		// {
		// 	if(!builtin_cd(ats->token))
		// 		return ;
		// 	ats = ats->next;
		// 	continue;
		// }
		// if (ats->token->type == WORD && ft_strlen(ats->token->str) == 4 && !ft_strncmp(ats->token->str, "echo", 5))
		// {
		// 	if(!builtin_echo(ats->token))
		// 		return ;
		// 	ats = ats->next;
		// 	continue;
		// }
		// if (ats->token->type == WORD && ft_strlen(ats->token->str) == 3 && !ft_strncmp(ats->token->str, "pwd", 4))
		// {
		// 	if(!builtin_pwd(ats->token))
		// 		return ;
		// 	ats = ats->next;
		// 	continue;
		// }
		// // export
		// if (ats->token->type == WORD && ft_strlen(ats->token->str) == 6 && !ft_strncmp(ats->token->str, "export", 7))
		// {
		// 	if(!builtin_export(ats->token))
		// 		return ;
		// 	ats = ats->next;
		// 	continue;
		// }
		// // env
		// if (ats->token->type == WORD && ft_strlen(ats->token->str) == 3 && !ft_strncmp(ats->token->str, "env", 4))
		// {
		// 	if(!builtin_env(ats->token))
		// 		return ;
		// 	ats = ats->next;
		// 	continue;
		// }
