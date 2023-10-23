/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/18 13:28:44 by svan-has      #+#    #+#                 */
/*   Updated: 2023/10/23 16:52:35 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"
#include "../../lib/libft/includes/libft.h"

void    parse_sphere(char ***split_line, t_data *data, int i)
{
    int j;
    int k;
    int count;

    count = 0;
    j = 0;
    while (split_line[j])
    {
        k = 0;
        while (split_line[j][k])
        {
            count++;
            k++;
        }
        j++;
    }
    if (count != 7)
        error_exit();
    printf("count: %d", count);
    data->objects[i].x = ft_atof(input_check(split_line[1][0]));
    // data->objects[i].y = ft_atof(input_check(split_line[1][1]));
    // data->objects[i].z = ft_atof(split_line[1][2]);
    // data->objects[i].diameter = ft_atof(split_line[2][0]);
    // data->objects[i].r = ft_atof(split_line[3][0]);
    // data->objects[i].g = ft_atof(split_line[3][1]);
    // data->objects[i].b = ft_atof(split_line[3][2]);

    // printf("x: %f\n", data->objects[i].x);
    // printf("y: %f\n", data->objects[i].y);

}