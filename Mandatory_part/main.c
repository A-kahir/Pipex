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

static	void	open_files(char **argv, int *infile, int *outfile)
{
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

static void	execute_first_cmd(int infile, int pp_fd[2], char **argv, char **env)
{
	char	**cmd;

	close(pp_fd[0]);
	cmd = ft_get_path(argv[2], env);
	if (!cmd || !cmd[0])
	{
		perror("Command not found");
		exit(1);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("dup2 input failed");
		exit(1);
	}
	if (dup2(pp_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 pipe failed");
		exit(1);
	}
	close(pp_fd[1]);
	close(infile);
	execve(cmd[0], cmd, env);
	perror("Execve failed");
	exit(1);
}

static void	execute_second_cmd(int outf, int pp_fd[2], char **argv, char **env)
{
	char	**cmd;

	close(pp_fd[1]);
	cmd = ft_get_path(argv[3], env);
	if (!cmd || !cmd[0])
		(perror("Command not found"), exit(1));
	if (dup2(pp_fd[0], STDIN_FILENO) == -1)
		(perror("dup2 pipe failed"), exit(1));
	if (dup2(outf, STDOUT_FILENO) == -1)
		(perror("dup2 output failed"), exit(1));
	close(pp_fd[0]);
	close(outf);
	execve(cmd[0], cmd, env);
	perror("Execve failed");
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
		(write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 40), exit(1));
	if (pipe(pipe_fd) == -1)
		(perror("Pipe creation failed"), exit(1));
	open_files(argv, &infile, &outfile);
	pid1 = fork();
	if (pid1 == -1)
		exit(1);
	else if (pid1 == 0)
		execute_first_cmd(infile, pipe_fd, argv, env);
	pid2 = fork();
	if (pid2 == -1)
		exit(1);
	else if (pid2 == 0)
		execute_second_cmd(outfile, pipe_fd, argv, env);
	ft_close_fd(&infile, &outfile, pipe_fd);
	return (waitpid(pid1, NULL, 0), waitpid(pid2, NULL, 0), 0);
}
