/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkostyla <wkostyla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:36:59 by wkostyla          #+#    #+#             */
/*   Updated: 2025/02/07 17:48:35 by wkostyla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_remove(char *buffer)
{
    char *line;
    int i;
    int j;

    i = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\0')
    {
        free(buffer);
        return (NULL);
    }
    line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
    i++;
    j = 0;
    while (buffer[i])
        line[j++] = buffer[i++];
    free(buffer);
    return(line);
}

char *ft_line(char *buffer)
{
    char *line;
    int i;

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
    return(line);
}

char *ft_join(char *temp, char *buffer)
{
    char *to_join;

    to_join = ft_strjoin(temp, buffer);
    free(temp);
    return (to_join);
}

char *ft_read(int fd, char* temp)
{
    char *buffer;
    int bytes;

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
        buffer[bytes] = 0;
        temp = ft_join(temp, buffer);
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    
    free(buffer);
    return(temp);
}

char *get_next_line(int fd)
{
    static char* buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
        return (NULL);
    buffer = ft_read(fd, buffer);
    if (!buffer)
        return (NULL);
    line = ft_line(buffer);
    buffer = ft_remove(buffer);
    return (line);
}