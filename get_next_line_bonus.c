/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 21:00:18 by ryhara            #+#    #+#             */
/*   Updated: 2023/06/10 21:00:18 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>

static char	*ft_read_line(int fd, char *buf, char **save)
{
	int	rbyte;

	rbyte = 1;
	while (rbyte)
	{
		rbyte = read(fd, buf, BUFFER_SIZE);
		if (rbyte == -1)
			return (NULL);
		if (rbyte == 0)
			return (save[fd]);
		buf[rbyte] = '\0';
		if (save[fd] == NULL)
			save[fd] = "";
		save[fd] = ft_strjoin(save[fd], buf);
		if (ft_strchr(buf, '\n'))
			break ;
		free(buf);
	}
	free(buf);
	return (save[fd]);
}

static char	*ft_get_line(int fd, char **save)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (save[fd][i] != '\n' && save[fd][i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j <= i)
	{
		line[j] = save[fd][j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_get_save(int fd, char **save)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_save;

	j = 0;
	i = 0;
	while (save[fd][i] != '\n' && save[fd][i] != '\0')
		i++;
	len = ft_strlen(save[fd]);
	if (i == len)
	{
		free(save[fd]);
		return (NULL);
	}
	i++;
	new_save = (char *)malloc(sizeof(char) * (len - i + 2));
	if (!new_save)
		return (NULL);
	while (save[fd][i] != '\0')
		new_save[j++] = save[fd][i++];
	new_save[j] = '\0';
	free(save[fd]);
	return (new_save);
}

static void	*free_all(char **save, char *buf)
{
	int	i;

	i = 0;
	while (i < 257)
	{
		free(save[i]);
		i++;
	}
	if (buf != NULL)
		free(buf);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*save[257];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX || fd > 256)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save[fd] = ft_read_line(fd, buf, save);
	if (!save[fd])
		return (free_all(save ,buf));
	line = ft_get_line(fd, save);
	if (!line)
		return (free_all(save, buf));
	save[fd] = ft_get_save(fd, save);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int	fd;
// 	int fd2;
// 	int fd3;
// 	char	*line;

// 	line = "";
// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);
// 	fd3 = open("test3.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("[%s]\n\n",line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("[%s]\n\n",line);
// 	line = get_next_line(fd3);
// 	printf("[%s]\n\n",line);
// 	line = get_next_line(fd);
// 	printf("[%s]\n\n",line);
// 	// while (line)
// 	// {
// 	// 	free(line);
// 	// 	line = get_next_line(fd);
// 	// 	printf("[%s]\n\n",line);
// 	// }
// 	printf("%d\n", BUFFER_SIZE);
// 	close(fd);
// }