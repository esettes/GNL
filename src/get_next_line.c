/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:41:44 by iostancu          #+#    #+#             */
/*   Updated: 2022/04/10 21:07:36 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_next(char *str)
{
	size_t	eol;
	size_t	str_len;
	size_t	i;
	char	*line;

	eol = ft_strlen(str, TRUE);
	if (!str[eol])
	{
		free(str);
		return (NULL);
	}
	str_len = ft_strlen(str, FALSE);
	line = (char *)malloc(sizeof(char) * (str_len - eol + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (eol + i < str_len)
	{
		line[i] = str[eol + i];
		i++;
	}
	line[i] = '\0';
	free (str);
	return (line);
}

char	*get_line(char *str)
{
	size_t	eol;
	char	*line;

	eol = 0;
	line = (char *)malloc(sizeof(char) * (ft_strlen(str, FALSE) + 1));
	if (str[0] == '\n')
	{
		line[0] = '\n';
		eol++;
	}
	while (str[eol - 1] != '\n' && str[eol])
	{
		line[eol] = str[eol];
		eol++;
	}
	line[eol] = '\0';
	return (line);
}

char	*read_fd(int fd, char *str)
{
	char	*buff;
	int		nbytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	nbytes = BUFFER_SIZE;
	while (!ft_strchr(str, '\n') && nbytes == BUFFER_SIZE)
	{
		nbytes = read(fd, buff, BUFFER_SIZE);
		if (nbytes == -1)
		{
			free (buff);
			return (NULL);
		}
		if (nbytes != 0)
		{
			buff[nbytes] = '\0';
			if (!str)
				str = ft_strdup(buff);
			else
				str = ft_strjoin(str, buff);
		}
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str_st;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1000)
		return (NULL);
	str_st = read_fd(fd, str_st);
	if (!str_st)
		return (NULL);
	line = get_line(str_st);
	str_st = get_next_next(str_st);
	return (line);
}

int	main(void)
{
	char	*line;
	int		file1 = open("tests/test.txt", O_RDONLY);
	int		file2 = open("tests/test2.txt", O_RDONLY);
	int		file3 = open("tests/test3.txt", O_RDONLY);
	printf("open limits: %i\n", OPEN_MAX);
	for (int k = 0; k < 6; k++)
		{
			line = get_next_line(file3);
			printf("file %i: %s\n", file3, line);
			free(line);
		}
	for (int j = 0; j < 4; j++)
		{
			line = get_next_line(file1);
			printf("file %i: %s\n", file1, line);
			free(line);
		}
		for (int i = 0; i < 7; i++)
		{
			line = get_next_line(file2);
			printf("file %i: %s\n", file2, line);
			free(line);
		}
	close(file1);
	close(file2);
	close(file3);

	return (0);
}
