/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 09:18:27 by yogun             #+#    #+#             */
/*   Updated: 2022/04/11 14:58:13 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int filedescriptor)
{
	static char	*all_file_characters;
	char		*line_from_parsing_at_newline;

	if (filedescriptor < 0 || BUFFER_SIZE <= 0)
		return (0);
	all_file_characters = read_from_passed_file(filedescriptor, all_file_characters);
	if (!all_file_characters)
		return (NULL);
	line_from_parsing_at_newline = ft_getline(all_file_characters);
	all_file_characters = ft_getrest(all_file_characters);
	return (line_from_parsing_at_newline);
}

/**
 * read the first line of a file descriptor
 */
char	*read_from_passed_file(int filedescriptor, char *characters_read)
{
	char	*temporary_characters_holder;
	int	number_of_characters_read;

	temporary_characters_holder = ft_strnew(BUFFER_SIZE + 1);
	number_of_characters_read = 1;
	while (!ft_strchr(characters_read, '\n') && (number_of_characters_read != 0))
	{
		number_of_characters_read = read(filedescriptor, temporary_characters_holder, BUFFER_SIZE);
		if (number_of_characters_read == -1)
		{
			free(temporary_characters_holder);
			return (NULL);
		}
		temporary_characters_holder[number_of_characters_read] = '\0';
		characters_read = ft_strjoin(characters_read, temporary_characters_holder);
	}
	free(temporary_characters_holder);
	return (characters_read);
}

/**
 * from the read string, take the first line and returns it
 */
char	*ft_getline(char *full_str)
{
	int		i;
	char	*line;

	i = 0;
	if (!full_str[i])
		return (NULL);
	while (full_str[i] && full_str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (full_str[i] && full_str[i] != '\n')
	{
		line[i] = full_str[i];
		i++;
	}
	if (full_str[i] == '\n')
	{
		line[i] = full_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/**
 * from the read string, take the first line and remove it. returns the rest
 */
char	*ft_getrest(char *full_str)
{
	int		i;
	int		j;
	char	*restof;

	i = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (!full_str[i])
	{
		free(full_str);
		return (NULL);
	}
	restof = (char *)malloc(sizeof(char) * (ft_strlen(full_str) - i + 1));
	if (!restof)
		return (NULL);
	i++;
	j = 0;
	while (full_str[i])
		restof[j++] = full_str[i++];
	restof[j] = '\0';
	//These last two command lines looks like wrong. So, I might need to update these two lines in repo. I will review it in 02.06.2022
	free(full_str);
	return (restof);
}
