/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 18:19:56 by akahir            #+#    #+#             */
/*   Updated: 2025/03/21 19:24:11 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_check_full_path(char **cmd_args)
{
	if (cmd_args[0][0] == '/' ||
		(cmd_args[0][0] == '.' && cmd_args[0][1] == '/'))
	{
		if (access(cmd_args[0], X_OK) == 0)
			return (1);
	}
	return (0);
}

char	**ft_search_in_path(char **cmd_args, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	while (env && env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env || !env[i])
		return (free_split(cmd_args), NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (free_split(cmd_args), NULL);
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin_free(full_path, cmd_args[0]);
		if (access(full_path, X_OK) == 0)
			return (free(cmd_args[0]), cmd_args[0] = full_path,
				free_split(paths), cmd_args);
		free(full_path);
		i++;
	}
	return (free_split(paths), free_split(cmd_args), NULL);
}

char	**ft_get_path(char *cmd, char **env)
{
	char	**cmd_args;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		return (NULL);
	if (ft_check_full_path(cmd_args))
		return (cmd_args);
	return (ft_search_in_path(cmd_args, env));
}
