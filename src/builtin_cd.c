/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:25:38 by kosnakam          #+#    #+#             */
/*   Updated: 2024/07/22 20:26:41 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	error_cd(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(path);
	error_status(1);
	free(path);
	return (true);
}

static char	*prev_path(char *path)
{
	int		i;
	int		j;
	char	*new_path;

	i = 0;
	j = 0;
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	while (path[i] != '/')
		i--;
	new_path = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_path)
		return (NULL);
	while (j < i)
	{
		new_path[j] = path[j];
		j++;
	}
	new_path[j] = '\0';
	return (new_path);
}

bool	do_cd(t_token *token, t_env **env, char *path)
{
	if (token->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (error_status(1), true);
	}
	else if (!ft_strncmp(token->str, "-", 1) && ft_strlen(token->str) == 1)
	{
		path = get_env_value("OLDPWD", *env);
		ft_putendl_fd(path, 1);
	}
	else if (!ft_strncmp(token->str, "~", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("HOME", *env);
	else if (!ft_strncmp(token->str, ".", 1) && ft_strlen(token->str) == 1)
		path = get_env_value("PWD", *env);
	else if (!ft_strncmp(token->str, "..", 2) && ft_strlen(token->str) == 2)
		path = prev_path(getcwd(NULL, 0));
	else path = ft_strdup(token->str);
	if (path && chdir(path) == -1)
		return (error_cd(path));
	edit_env_value("OLDPWD", get_env_value("PWD", *env), env);
	edit_env_value("PWD", getcwd(NULL, 0), env);
	error_status(0);
	free(path);
	return (true);
}

bool	builtin_cd(t_token *token, t_env **env)
{
	char	*path;

	path = NULL;
	if (!token->next)
	{
		path = get_env_value("HOME", *env);
		if (!path)
			return (ft_putendl_fd("cd: HOME not set", 2),
				error_status(1), true);
		else if (path[0] == '\0')
			return (free(path), true);
		if (chdir(path) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(path);
			return (error_status(1), free(path), true);
		}
		edit_env_value("OLDPWD", get_env_value("PWD", *env), env);
		edit_env_value("PWD", getcwd(NULL, 0), env);
		return (true);
	}
	token = token->next;
	return (do_cd(token, env, path));
}
