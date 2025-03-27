/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:57:47 by akahir            #+#    #+#             */
/*   Updated: 2025/03/05 13:57:47 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

char	**ft_get_path(char *argv, char **env);

//utils_functions:
int		ft_strncmp( char *s1, char *s2, size_t n);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(const char *s, char c);
void	free_split(char **split);
char	*ft_strdup(char *s1);
char	*ft_strjoin_free(char *s1, char *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_close_fd(int *infile, int *outfile, int pipe_fd[2]);
char	*ft_strchr(const char *s, int c);

#endif