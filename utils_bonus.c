/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:55:12 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/21 14:04:37 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i++])
		free(paths[i]);
	free(paths);
}

char	*find_path(char *command, char **env)
{
	char	**paths;
	char	*path;
	char	*mini_path;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		mini_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(mini_path, command);
		free(mini_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	free_paths(paths);
	return (0);
}

void	ft_error(char *s)
{
	perror(s);
	exit(1);
}
