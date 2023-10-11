/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 15:17:48 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/10 13:46:50 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include <stdio.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;

}t_vec;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}t_color;

uint32_t get_rgba(double r, double g, double b, double a);

#endif