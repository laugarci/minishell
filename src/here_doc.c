/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:32:55 by ffornes-          #+#    #+#             */
/*   Updated: 2023/06/27 16:53:11 by ffornes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static char	*get_delimiter(char **input)
{
	char	*out;
	char	*aux;
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_strnstr(input[i], "<<", ft_strlen(input[i])))
			break ;
		i++;
	}
	out = ft_strdup("");
	aux = out;
	if (input[i][0] == '<' && input[i][1] == '<')
	{
		if (ft_strlen(input[i]) > 2)
		{
			free(aux);
			out = ft_strdup(input[i]);
			if (!out)
				return (NULL);
			aux = out;
			out = ft_strtrim(out, "<<");
			free(aux);
		}
		else
		{
			free(aux);
			out = ft_strdup(input[i + 1]);
			if (!out)
				return (NULL);
		}
	}
	return (out);
}

char	*here_doc(char **input, char *envp[])
{
	char	*line;
	char	*aux;
	char	*tmp;
	char	*delimiter;

	delimiter = get_delimiter(input);
	if (!delimiter)
		return (NULL);
	aux = ft_strdup("");
	while (1)
	{
		ft_putstr_fd("heredoc> ", 0);
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, (int)ft_strlen(delimiter)))
			break ;
		tmp = aux;
		aux = ft_strjoin(aux, line);
		free(tmp);
		free(line);
	}
	free(line);
	free(delimiter);
	printf("%s", aux);
	free(aux);
	if (envp)
		return (NULL);
	return (NULL);
}
