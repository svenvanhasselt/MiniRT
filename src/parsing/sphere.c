/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:28:44 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/18 16:47:14 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void    parse_sphere(char **split_line, t_data *data)
{
    int i;

    i = 0;
    while (split_line[i])
    {
        data->objects[0].x = ft_atof(split_line[i]);
        printf("F: %d\n", data->objects[0].x);
        printf("i: %d s: %s\n", i, split_line[i]);
        i++;
    }
}