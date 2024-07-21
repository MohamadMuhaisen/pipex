/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:55:00 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/21 15:08:29 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parse_cmd(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], env);
	if (!path)
	{
		free_paths(cmd);
		ft_error("Error!\n");
	}
	if (execve(path, cmd, env) == -1)
		ft_error("Error!\n");
}

void	child_process(char **argv, char **env, t_elem *elem, int cmd_index)
{
	int	i;

	i = 0;
	if (cmd_index == 0)
	{
		if (dup2(elem->infile, STDIN_FILENO) == -1)
			ft_error("dup2 failed infile\n");
		if (dup2(elem->pipefd[1], STDOUT_FILENO) == -1)
			ft_error("dup2 failed stdout\n");
	}
	else if (cmd_index == elem->num_cmds - 1)
	{
		if (dup2(elem->pipefd[2 * (cmd_index - 1)], STDIN_FILENO) == -1)
			ft_error("dup2 failed pipe in\n");
		if (dup2(elem->outfile, STDOUT_FILENO) == -1)
			ft_error("dup2 failed outfile\n");
	}
	else
		if (dup2(elem->pipefd[2 * (cmd_index - 1)], STDIN_FILENO) == -1
			|| dup2(elem->pipefd[2 * cmd_index + 1], STDOUT_FILENO) == -1)
			ft_error("dup2 failed pipe\n");
	while (i < 2 * (elem->num_cmds - 1))
		close(elem->pipefd[i++]);
	parse_cmd(argv[cmd_index + 2], env);
}

void	init_elem(t_elem *elem, int num_cmds, char **argv)
{
	int	i;

	i = 0;
	elem->pipefd = (int *)malloc((2 * (num_cmds - 1)) * sizeof(int));
	if (!elem->pipefd)
		ft_error("Malloc failed");
	elem->infile = open(argv[1], O_RDONLY);
	if (elem->infile == -1)
		ft_error("infile open failed\n");
	elem->outfile = open(argv[num_cmds + 2], O_WRONLY
			| O_CREAT | O_TRUNC, 0644);
	if (elem->outfile == -1)
		ft_error("outfile open failed\n");
	while (i < num_cmds - 1)
	{
		if (pipe(elem->pipefd + 2 * i) == -1)
			ft_error("pipe failed\n");
		i++;
	}
	elem->num_cmds = num_cmds;
}

int	pipex(char **argv, char **env, int num_cmds)
{
	t_elem	elem;
	pid_t	pid;
	int		status;
	int		i;

	init_elem(&elem, num_cmds, argv);
	i = -1;
	while (++i < num_cmds)
	{
		pid = fork();
		if (pid == 0)
			child_process(argv, env, &elem, i);
		else if (pid < 0)
			ft_error("fork failed\n");
	}
	i = 0;
	while (i < 2 * (num_cmds - 1))
		close(elem.pipefd[i++]);
	close(elem.infile);
	close(elem.outfile);
	i = 0;
	while (i++ < num_cmds)
		waitpid(-1, &status, 0);
	free(elem.pipefd);
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
		return (1);
	}
	return (pipex(argv, env, argc - 3));
}
