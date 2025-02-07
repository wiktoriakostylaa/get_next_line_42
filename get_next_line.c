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

char *read_fd(int fd, char* temp)
{
    char *buffer;
    int bytes;

    if (!temp)
        temp = ft_calloc(1, 1);
    buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    bytes = 1;
    while (bytes > 1)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == -1)
        {
            free(buffer);
            return (NULL);
        }
        buffer[bytes] = 0;
        //join and free ???????????????/
        if (ft_strchr(buffer, '\n'))
            break;
    }
    
    free(buffer);
    return(temp);
}

char* get_next_line(int fd)
{
    static char* buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
        return (NULL);
    buffer = read_fd(fd, buffer);
}