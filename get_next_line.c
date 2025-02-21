/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkostyla <wkostyla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:36:59 by wkostyla          #+#    #+#             */
/*   Updated: 2025/02/18 16:37:42 by wkostyla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* Usuwa przetworzona czesc bufora i zostawia tylko to co jest
   po pierwszym wystapieniu \n. Odpowiada za przechowywanie
   pozostałych danych po tym, jak pierwsza linia została odczytana.
*/
char	*ft_remove(char *buffer)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new_line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		new_line[j++] = buffer[i++];
	free(buffer);
	return (new_line);
}

/* Tworzy i zwraca linie do \n z bufora.
   Wyciaga pierwsza linie z bufora.*/
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

/* Laczy dwa ciagi znakow: dotychczas odczytane (temp)
   i nowy fragment (buffer).
   Obsluza wypadek gdzie zadne dane nie zostaly odczytane.
*/
char	*ft_join(char *temp, char *buffer, int bytes)
{
	char	*to_join;

	if (bytes == 0 && ft_strlen(temp) == 0)
	{
		free(temp);
		return (NULL);
	}
	to_join = ft_strjoin(temp, buffer);
	free(temp);
	return (to_join);
}

/* Czyta dane z pliku do bufora i laczy z dotychczasowymi
   danymi.
*/
char	*ft_read(int fd, char *temp)
{
	char	*buffer;
	int		bytes;

	if (!temp)
		temp = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		temp = ft_join(temp, buffer, bytes);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (temp);
}

/* Glowna funkcja programu ktora zwraca jedna linie tekstu
   z pliku przy kazdym wywolaniu.
*/
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	buffer = ft_remove(buffer);
	return (line);
}
