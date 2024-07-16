/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:45:44 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/07/16 18:24:51 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	process1(char **argv, char **env, int pipefd[2])
{
	int	infile;

	infile = open(argv[1], 0);
	if (infile == -1)
		ft_error("infile open failed\n");
	if (dup2(infile, STDIN_FILENO) == -1)
		ft_error("dup2 failed stdin\n");
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		ft_error("dup2 failed stdout\n");
	close (pipefd[0]);
	close (pipefd[1]);
	close (infile);
	parse_cmd(argv[2], env);
}

void	process2(char **argv, char **env, int pipefd[2])
{
	int	outfile;

	outfile = open(argv[4], 1);
	if (outfile == -1)
		ft_error("outfile open failed\n");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		ft_error("dup2 failed pipefd[0]\n");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		ft_error("dup2 failed outfile\n");
	close (pipefd[0]);
	close (pipefd[1]);
	close (outfile);
	parse_cmd(argv[3], env);
}

int	pipex(char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		status;

	if (pipe(pipefd) == -1)
		ft_error("pipe failed!\n");
	pid1 = fork();
	if (pid1 == 0)
		process1(argv, env, pipefd);
	pid2 = fork();
	if (pid2 == 0)
		process2(argv, env, pipefd);
	close (pipefd[0]);
	close (pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	return (pipex(argv, env));
}
