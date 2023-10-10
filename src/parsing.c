/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 12:06:04 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/10 13:03:52 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "../lib/libft/includes/libft.h"
#include<fcntl.h> 

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
void    parse_input(int argc, char **argv)
{
    int rt_file;

    error_check(argc, argv);
    rt_file = open (argv[1], O_RDONLY);
    if (rt_file < 0)
        error_exit();
    
    
}