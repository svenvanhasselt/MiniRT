/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:06:04 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/18 16:33:54 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h> 

void    error_check(int argc, char **argv)
{
    int len;

    if (argc != 2)
        error_exit();
    len = ft_strlen(argv[1]);
    if (len < 4)
        error_exit();
    if (ft_strncmp(argv[1] + (len - 3), ".rt", 3))
        error_exit();
}

void    process_split_line(char **split_file, t_data *data)
{
    int     i;
    char    **split_line;

    (void)data;
    split_line = NULL;
    if (line_check_object(split_file[0]))
    {
        i = 1;
        while (split_file[i])
        {
            split_line = null_check(ft_split(split_file[i], ','));
            parse_sphere(split_line, data);
            free_split(split_line);
            i++;
        }
    }
}

char   **process_file(char *file, t_data *data)
{
    int     rt_file;
    char    *line;
    char    **split_line;

    split_line = NULL;
    (void)data;
    rt_file = open (file, O_RDONLY);
    if (rt_file < 0)
        error_exit();
    while(1)
    {
        line = get_next_line(rt_file);
        if (!line)
            break;
        if (line_check_data(line) || line_check_object(line))
        {
            replace_char(&line, '\t', ' ');
            split_line = null_check(ft_split(line, ' '));
            process_split_line(split_line, data);
        }
        free(line);
    }
    close (rt_file);
    return (split_line);
}

void    parse_input(int argc, char **argv, char ***split_file, t_data *data)
{
    error_check(argc, argv);
    count_objects(argv[1], data);
    *split_file = process_file(argv[1], data);
}