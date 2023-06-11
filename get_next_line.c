/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryhara <ryhara@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:39:38 by ryhara            #+#    #+#             */
/*   Updated: 2023/06/11 17:23:47 by ryhara           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *buf, char *save)
{
	int	rbyte;

	rbyte = 1;
	while (rbyte)
	{
		rbyte = read(fd, buf, BUFFER_SIZE);
		if (rbyte == -1)
			return (NULL);
		if (rbyte == 0)
			return (NULL);
		buf[rbyte] = '\0';
		if (save == NULL)
			save = "";
		save = ft_strjoin(save, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (save);
}

char	*ft_get_line(char *save)
{
	char	*line;
	size_t	i;
	size_t	j;
	size_t	save_len;

	i = 0;
	j = 0;
	save_len = ft_strlen(save);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (i == save_len)
		return (save);
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j <= i)
	{
		line[j] = save[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_get_save(char *save)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*new_save;

	j = 0;
	i = 0;
	while (save[i] != '\n')
		i++;
	i++;
	len = ft_strlen(save);
	if (i == len)
	{
		free(save);
		return (NULL);
	}
	new_save = (char *)malloc(sizeof(char) * (len - i + 2));
	if (!new_save)
		return (NULL);
	while (save[i] != '\0')
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	return (new_save);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*save[257];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	save[fd] = ft_read_line(fd, buf, save[fd]);
	if (!save[fd])
	{
		free(buf);
		return (NULL);
	}
	line = ft_get_line(save[fd]);
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	save[fd] = ft_get_save(save[fd]);
	free(buf);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>
// int	main(void)
// {
// 	int	fd;
// 	char	*line;

// 	line = "";
// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s",line);
// 	// printf("[ans1:%s]\n\n",line);
// 	// free(line);
// 	// line = get_next_line(fd);
// 	// printf("[ans2:%s]\n\n",line);
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		printf("[%s]\n\n",line);
// 	}
// 	printf("%d\n", BUFFER_SIZE);
// 	close(fd);
// }