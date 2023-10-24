/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:06:04 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/24 17:55:29 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"
#include <fcntl.h> 

void    error_check(int argc, char **argv)
{
    int len;

    if (argc != 2)
        error_exit("Needs an .rt file as input");
    len = ft_strlen(argv[1]);
    if (len < 4)
        error_exit("Needs an .rt file as input");
    if (ft_strncmp(argv[1] + (len - 3), ".rt", 3))
        error_exit("Needs an .rt file as input");
}

void    check_object_data(char *string,  char ***split_line, t_data *data, int i)
{
    if (!ft_strncmp(string, "sp", ft_strlen(string)))
        parse_sphere(split_line, data, 0);
    if (!ft_strncmp(string, "pl", ft_strlen(string)))
        parse_plane(split_line, data, 0);
    // if (!ft_strncmp(string, "cy", ft_strlen(string)))
    //     parse_cylinder(split_line, data, 0);
    if (!ft_strncmp(string, "A", ft_strlen(string)))
        parse_amb_light(split_line, data);
    if (!ft_strncmp(string, "c", ft_strlen(string)))
        parse_camera(split_line, data);
    if (!ft_strncmp(string, "l", ft_strlen(string)))
        parse_light(split_line, data);
}
void    process_split_line(char **split_file, t_data *data)
{
    int     i;
    char    ***split_line;

    (void)data;
    split_line = NULL;
    i = 0;
    while (split_file[i])
        i++;
    printf("i: %d\n", i);
    split_line = null_check(malloc ((i) * sizeof(char **)));
    if (line_check_object(split_file[0]) || line_check_data(split_file[0]))
    {
        i = 0;
        while (split_file[++i])
            split_line[i - 1] = null_check(ft_split(split_file[i], ','));
        split_line[i - 1] = NULL;
        printf("i - 0: %d\n", i -1);
    }
    check_object_data(split_file[0], split_line, data, i);    
    i = 0;
    while (split_line[i])
    {
        free_split(split_line[i]);
        i++;
    }
    free(split_line);
    free_split(split_file);
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
        error_exit("Cannot open file");
    while(1)
    {
        line = get_next_line(rt_file);
        if (!line)
            break;
        if (line_check_data(line) || line_check_object(line))
        {
            replace_char(&line, '\t', ' ');
            line = null_check(ft_strtrim_free(line, "\n"));
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