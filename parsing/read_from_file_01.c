/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_file_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:27:25 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/22 22:35:10 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	ft_check_first_param(char *s)
{
	return (!ft_strcmp(s, "A") || !ft_strcmp(s, "L") || !ft_strcmp(s, "C")
		|| !ft_strcmp(s, "pl") || !ft_strcmp(s, "sp") || !ft_strcmp(s, "cy")
		|| !ft_strcmp(s, "cn"));
}

int	ft_read_lines_from_file(char *filename)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_print_and_exit("Error when opening file", 1), -1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	ft_count_line(char *filename)
{
	int	i;

	i = ft_read_lines_from_file(filename);
	if (i == -1)
		return (-1);
	if (i > 2147483647)
	{
		ft_print_and_exit("Max Number of lines exceeded!", 1);
		return (-1);
	}
	return (i);
}

void	ft_line_utils(int *c, int fd, char **lst)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "") || !ft_strcmp(line, "\n"))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else
		{
			(*c)++;
			lst[i] = line;
		}
		i++;
		line = get_next_line(fd);
	}
	lst[i] = NULL;
}

char	**ft_lines(char *filename)
{
	int		fd;
	char	**lst;
	int		c;

	fd = open(filename, O_RDONLY);
	lst = malloc((ft_count_line(filename) + 1) * sizeof(char *));
	if (fd < 0)
	{
		perror("Error when openning file\n");
		free(lst);
		return (NULL);
	}
	c = 0;
	ft_line_utils(&c, fd, lst);
	close(fd);
	if (c == 0)
		return (ft_print_and_exit("Empty file", 1), NULL);
	ft_count_line(filename);
	return (lst);
}
