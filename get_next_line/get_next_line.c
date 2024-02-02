/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:33:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 12:15:45 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char			*str_joined;
	unsigned int	i;
	unsigned int	j;

	str_joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str_joined == NULL)
		return (NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{
			str_joined[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str_joined[i + j] = s2[j];
		j++;
	}
	str_joined[i + j] = '\0';
	return (str_joined);
}

static char	*append_str(int fd, char *str)
{
	char	*buffer;
	int		a;
	char	*tmp;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (buffer == NULL)
		return (NULL);
	while (ft_strchr_mod(buffer, '\n') == NULL)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a < 0)
		{
			free(buffer);
			return (NULL);
		}
		else if (a == 0)
			break ;
		buffer[a] = '\0';
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
	}
	free(buffer);
	return (str);
}

static char	*update_str(char *line)
{
	char	*new_str;
	int		i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new_str = ft_strdup_mod(line + i + 1);
	if (*new_str == '\0')
	{
		free(new_str);
		new_str = NULL;
	}
	return (new_str);
}

static char	*extract_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = ft_calloc(i + 1, 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i] = line[i];
	free(line);
	return (str);
}

char	*get_next_line(int fd, int i)
{
	static char	*str;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = append_str(fd, str);
	if (line == NULL)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = update_str(line);
	line = extract_line(line);
	if (i == 1)
	{
		free(str);
		str = NULL;
	}
	return (line);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*line;
// 	int		i = 1;
// 	// int		fd;

// 	fd = open("otherfile.txt", O_RDONLY);
// 	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
// 	while (i < 5)
// 	{
// 		line = get_next_line(fd);
// 		printf("line3-%d: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	// close(fd);
// 	return (0);
// }
