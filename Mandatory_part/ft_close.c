/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:53:43 by akahir            #+#    #+#             */
/*   Updated: 2025/03/27 15:29:05 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_close_fd(int *infile, int *outfile, int pipe_fd[2])
{
	close(*infile);
	close(*outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
