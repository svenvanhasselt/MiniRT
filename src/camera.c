/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 15:44:38 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/18 11:21:12 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	init_camera(t_data *data, float j, float i)
{
	t_vec world_up_vec = set_vec(0,1,0);
	t_vec	heart;
	t_vec	move_left;
	t_vec	move_up;
	
	data->camera.right = unit_vector(cross( world_up_vec, data->camera.ovec));	
	data->camera.up = unit_vector(cross(data->camera.ovec, data->camera.right));
	heart = add(data->camera.vec, mult_fact(data->camera.ovec, data->camera.focal_length));
	move_left = sub(heart, mult_fact(data->camera.right,data->viewport_w/2 - j));
	move_up = add(move_left,mult_fact(data->camera.up,data->viewport_h/2 - i));
	return (move_up);
}
