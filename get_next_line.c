/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkostyla <wkostyla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:36:59 by wkostyla          #+#    #+#             */
/*   Updated: 2025/02/07 16:38:36 by wkostyla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_fd(int fd, char* result)
{
    char *buffer;
    int bytes;

    if (!result)
        result = ft_calloc(1, 1);
}

char* get_next_line(int fd)
{
    static char* buffer;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
        return (NULL);
    buffer = read_fd(fd, buffer);
}