/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:57:10 by akahir            #+#    #+#             */
/*   Updated: 2025/03/05 13:57:10 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	check_commands(char **argv)
{
	if ((argv[2][0] == '.' || argv[2][0] == '/'
		|| (argv[2][0] == '.' && argv[2][1] == '/') || (argv[3][0] == '.' ||
			argv[3][0] == '/' || (argv[3][0] == '.' && argv[3][0] == '/'))))
	{
		if (argv[3][0] == '.' || argv[3][0] == '/'
			|| (argv[3][0] == '.' && argv[3][0] == '/'))
		{
			return (perror("no such file or directory"), exit(1), 0);
		}
		return (perror("no such file or directory"), 0);
	}
	return (1);
}

static	void	open_files(char **argv, int *infile, int *outfile)
{
	check_commands(argv);
	*infile = open(argv[1], O_RDONLY);
	if (*infile < 0)
	{
		perror("Error opening input file");
		*infile = open("/dev/null", O_RDONLY);
		if (*infile < 0)
			exit(1);
	}
	*outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile < 0)
	{
		perror("Error opening output file");
		close(*infile);
		exit(1);
	}
}

static	void	ex_fir_cmd(int infile, int pipe_fd[2], char **argv, char **env)
{
	char	**cmd;

	close(pipe_fd[0]);
	cmd = ft_get_path(argv[2], env);
	if (!cmd || !cmd[0])
	{
		perror("Command not found");
		exit(1);
	}
	dup2(infile, 0);
	close(infile);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	execve(cmd[0], cmd, env);
	perror("Command execution failed");
	exit(1);
}

static	void	ex_sec_cmd(int outfile, int pipe_fd[2], char **argv, char **env)
{
	char	**cmd;

	close(pipe_fd[1]);
	cmd = ft_get_path(argv[3], env);
	if (!cmd || !cmd[0])
	{
		perror("Command not found");
		exit(1);
	}
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	dup2(outfile, 1);
	close(outfile);
	execve(cmd[0], cmd, env);
	perror("Command execution failed");
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		infile;
	int		outfile;
	int		pipe_fd[2];

	if (argc != 5)
		return (perror("Usage: infile cmd1 cmd2 outfile"), exit(1), 0);
	if (pipe(pipe_fd) == -1)
		return (perror("Pipe creation failed"), exit(1), 0);
	open_files(argv, &infile, &outfile);
	pid1 = fork();
	if (pid1 < 0)
		return (perror("Fork failed"), exit(1), 1);
	else if (pid1 == 0)
		ex_fir_cmd(infile, pipe_fd, argv, env);
	pid2 = fork();
	if (pid2 < 0)
		return (perror("Fork failed"), exit(1), 0);
	else if (pid2 == 0)
		ex_sec_cmd(outfile, pipe_fd, argv, env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(infile);
	return (close(outfile), waitpid(pid1, NULL, 0), waitpid(pid2, NULL, 0), 0);
}
