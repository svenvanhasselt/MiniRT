/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/18 10:31:55 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include "lib/mlx42/include/MLX42/MLX42.h"
#include <stdio.h>

enum   t_type
{
    sphere,
    cilinder,
};

typedef struct s_object
{
    int id;
    
}   t_object;

void    parse_input(int argc, char **argv);
void    error_exit(void);
void    *null_check(void *check);

#endif