/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 20:12:09 by kbassim           #+#    #+#             */
/*   Updated: 2024/03/28 16:19:13 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_line(char *txt)
{
	char	*str;
	int		i;

	i = 0;
	if (!txt[i])
		return (NULL);
	while (txt[i] && txt[i] != '\n')
		i++;
	if (txt[i] == '\n')
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (txt[i] && txt[i] != '\n')
	{
		str[i] = txt[i];
		i++;
	}
	if (txt[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static char	*get_after_line(char *txt)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (!txt || !txt[i])
		return (NULL);
	while (txt[i] && txt[i] != '\n')
		i++;
	if (txt[i] == '\n')
		i++;
	str = malloc((ft_strlen(txt) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	while (txt[i])
		str[j++] = txt[i++];
	str[j] = '\0';
	free(txt);
	if (!str[0])
	{
		free(str);
		str = NULL;
	}
	return (str);
}

static char	*get_txt(int fd, char *buff, char *txt)
{
	ssize_t	j;

	j = 1;
	while (j > 0)
	{
		j = read(fd, buff, BUFFER_SIZE);
		if (j < 0)
		{
			free(txt);
			return (NULL);
		}
		if (j == 0)
			return (txt);
		buff[j] = '\0';
		txt = ft_strjoin(txt, buff);
		if (!txt)
			return (NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (txt);
}

static char	*read_file(int fd, char *txt)
{
	char	*buff;

	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	txt = get_txt(fd, buff, txt);
	free(buff);
	return (txt);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*txt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	txt = read_file(fd, txt);
	if (!txt)
		return (NULL);
	line = get_line(txt);
	if (!line)
	{
		free(txt);
		txt = NULL;
	}
	txt = get_after_line(txt);
	return (line);
}
