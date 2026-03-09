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
	static char	*characters_read_from_file;
	char		*characters_before_newline;

	if (filedescriptor < 0 || BUFFER_SIZE <= 0)
		return (0);
	characters_read_from_file = read_from_passed_file_till_newline(filedescriptor, characters_read_from_file);
	if (!characters_read_from_file)
		return (NULL);
	characters_before_newline = extract_characters_before_newline(characters_read_from_file);
	characters_read_from_file = get_remaining_characters_after_newline(characters_read_from_file);
	return (characters_before_newline);
}

char	*read_from_passed_file_till_newline(int filedescriptor, char *characters_read)
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

char	*extract_characters_before_newline(char *characters_read)
{
	int		i;
	char	*characters_before_newline;

	i = 0;
	if (!characters_read[i])
		return (NULL);
	while (characters_read[i] && characters_read[i] != '\n')
		i++;
	characters_before_newline = ft_strnew(i + 2);
	i = 0;
	while (characters_read[i] && characters_read[i] != '\n')
	{
		characters_before_newline[i] = characters_read[i];
		i++;
	}
	if (characters_read[i] == '\n')
	{
		characters_before_newline[i] = characters_read[i];
		i++;
	}
	characters_before_newline[i] = '\0';
	return (characters_before_newline);
}

char	*get_remaining_characters_after_newline(char *remaining_characters)
{
	int	i;
	int	j;
	char	*characters_to_store;

	i = 0;
	while (remaining_characters[i] && remaining_characters[i] != '\n')
		i++;
	if (!remaining_characters[i])
	{
		free(remaining_characters);
		return (NULL);
	}

	characters_to_store = ft_strnew(ft_strlen(remaining_characters) - i + 1);

	i++;
	j = 0;
	while (remaining_characters[i])
		characters_to_store[j++] = remaining_characters[i++];
	characters_to_store[j] = '\0';
	free(remaining_characters);
	return (characters_to_store);
}
