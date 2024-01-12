/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 15:44:38 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/12 16:55:00 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec	init_camera(t_data *data, float j, float i)
{
	t_vec world_up_vec = set_vec(0,1,0);
	t_vec	heart;
	t_vec	move_left;
	t_vec	move_up;
	
	data->camera.right = unit_vector(cross(data->camera.ovec, world_up_vec));
	//printf("%f,%f,%f\n",data->camera.right.x,data->camera.right.y,data->camera.right.z);
	
	data->camera.up = unit_vector(cross(data->camera.right, data->camera.ovec));
	//printf("%f,%f,%f\n",data->camera.up.x,data->camera.up.y,data->camera.up.z);
	
	heart = add(data->camera.vec, mult_fact(data->camera.ovec, data->camera.focal_length));
	//printf("%f,%f,%f\n%f\n",heart.x,heart.y,heart.z,data->camera.focal_length);
	
	move_left = sub(heart, mult_fact(data->camera.right,data->viewport_w/2 - j));

	move_up = add(move_left,mult_fact(data->camera.right,data->viewport_h/2 - i));
	printf("%f,%f,%f\n",move_up.x,move_up.y,move_up.z);
	return (move_up);
}
