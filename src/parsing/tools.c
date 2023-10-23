/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:04:12 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/23 16:27:42 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h>

bool   line_check_object(char *line)
{
    if ((line[0] && line[1]) && (!ft_strncmp(line, "sp", 2) ||\
    !ft_strncmp(line, "pl", 2) || !ft_strncmp(line, "cy", 2)))
        return (true);
    return (false);
}

bool   line_check_data(char *line)
{
    if (line[0] && (line[0] == 'A' || line[0] == 'C' || line[0] == 'L'))
        return (true);
    if (line[0] && (line[0] == 'a' || line[0] == 'c' || line[0] == 'l'))
        return (true);
    return (false);
}

void    replace_char(char **string, char a, char b)
{
    int i;

    i = 0;
    while ((*string)[i])
    {
        if ((*string)[i] == a)
            (*string)[i] = b;
        i++;
    }
}

void    count_objects(char *file, t_data *data)
{
    int     rt_file;
    char    *line;

    rt_file = open (file, O_RDONLY);
    if (rt_file < 0)
        error_exit();
    while(1)
    {
        line = get_next_line(rt_file);
        if (!line)
            break;
        if (line_check_object(line))
            data->object_num++;
        free(line);
    }
    data->objects = null_check(malloc (data->object_num * sizeof(t_object)));
    close(rt_file);
}

void    free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
