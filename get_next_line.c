/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaby <ibaby@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:20:39 by ibaby             #+#    #+#             */
/*   Updated: 2024/05/30 21:10:34 by ibaby            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	save[BUFFER_SIZE + 1];
	char		*str;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	byte_read = 1;
	str = ft_strdup(save);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str || !buffer)
		return (free(buffer), free(str), NULL);
	while (is_nl(str) == 0 && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
			return (ft_clean(save), free(buffer), free(str), NULL);
		free((buffer[byte_read] = '\0', str = ft_strjoin(str, buffer), NULL));
		if (!str)
			return (free(buffer), NULL);
	}
	free((after_line(str, save), str = before_line(str), buffer));
	if (!str)
		return (NULL);
	return (str);
}

void	ft_clean(char *save)
{
	size_t	i;

	i = 0;
	if (!*save)
		return ;
	while (save[i] != '\n' && save[i])
	{
		save[i] = '\0';
		i++;
	}
	ft_strcpy(save, save + i + 1);
}

void	after_line(char *all, char *dest)
{
	int	i;

	i = 0;
	if (!all)
		return ;
	while (all[i] != '\n' && all[i])
		i++;
	if (all[i] == '\n')
		i++;
	else
	{
		*dest = '\0';
		return ;
	}
	ft_strcpy(dest, all + i);
}

char	*before_line(char *all)
{
	int		i;
	char	*dest;
	int		test;

	i = 0;
	if (!all)
		return (NULL);
	while (all[i] != '\n' && all[i])
		i++;
	if (all[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	test = i;
	while (i >= 0)
	{
		dest[i] = all[i];
		i--;
	}
	dest[test] = '\0';
	free(all);
	return (dest);
}
