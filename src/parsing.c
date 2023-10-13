/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:06:04 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/11 14:36:51 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "../lib/libft/includes/libft.h"
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

bool    rt_line_check(char *line)
{
    if (line[0] && (line[0] == 'A' || line[0] == 'C' || line[0] == 'L'))
        return (true);
    if ((line[0] && line[1]) && (!ft_strncmp(line, "sp", 2) ||\
    !ft_strncmp(line, "pl", 2) || !ft_strncmp(line, "cy", 2)))
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

void    process_file(char *file)
{
    int     rt_file;
    char    *line;
    char    **split_line;

    rt_file = open (file, O_RDONLY);
    if (rt_file < 0)
        error_exit();
    while(1)
    {
        line = get_next_line(rt_file);
        if (!line)
            break;
        if (rt_line_check(line))
        {
            replace_char(&line, '\t', ' ');
            split_line = null_check(ft_split(line, ' '));
            int i = 0;
            while (split_line[i])
            {
                printf("i: %d s: %s\n", i, split_line[i]);
                i++;
            }
        }
        free(line);

    }
}

void    parse_input(int argc, char **argv)
{
    error_check(argc, argv);
    process_file(argv[1]);
}