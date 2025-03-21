/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akahir <akahir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:00:06 by akahir            #+#    #+#             */
/*   Updated: 2025/03/21 22:27:32 by akahir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
	{
		return (0);
	}
	i = 0;
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
		{
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
		}
		if (s1[i] != s2[i])
		{
			return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
		}
		i++;
	}
	return (0);
}
