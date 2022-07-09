/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hykang <hykang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 13:17:12 by hykang            #+#    #+#             */
/*   Updated: 2022/07/09 02:20:26 by hykang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *backup)
{
	char	*buf;
	int		rbytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rbytes = 1;
	while (rbytes != 0)
	{
		rbytes = read(fd, buf, BUFFER_SIZE);
		if (rbytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rbytes] = '\0';
		backup = ft_strjoin(backup, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (backup);
}

char	*get_line(char	*backup)
{
	char	*buf;
	int		i;

	i = 0;
	if (!backup[0])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	buf = (char *)malloc(sizeof(char) * (i + 1));
	if (!buf)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		buf[i] = backup[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*backup_next(char	*backup)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	buf = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!buf)
		return (NULL);
	i++;
	j = 0;
	while (backup[i])
		buf[j++] = backup[i++];
	buf[j] = '\0';
	free(backup);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	backup = read_and_store(fd, backup);
	if (!backup)
		return (NULL);
	buf = get_line(backup);
	backup = backup_next(backup);
	return (buf);
}
