/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/10 14:18:48 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

//make a object list
bool	hit_object(t_data *data, int v)
{
	int i;

	i = 0;
	data->all_ray[v].t = -1;

	while (i < data->object_num)
	{
		if (data->objects[i].type == sphere && hit_sphere(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == plane && hit_plane(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == cylinder && hit_cylinder(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == cone && hit_cone(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		i++;
	}
	return (false);
}

t_vec	set_facenorm(t_vec ray_dir, t_vec face)//calculate if the ray hit the outside of sphere
{
	if (dot(ray_dir, face) > 0.0)//ray hit inside of sphere
		return (set_vec(-face.x, -face.y, -face.z));// face = -face
	else
		return (face);
}

void init_pix(t_data *data)
{
	int v;
	int j;
	int i;

	v = 0;
	j = 0;
	data->all_pix = malloc ((data->viewport_w * data->viewport_h) * sizeof(t_pixel));
	while (j < data->viewport_w)
	{
		i = 0;
		while (i <data->viewport_h)
		{
			data->all_pix[v] = set_pixel(data->all_ray[v], j, i, 255);
			v++;
			i++;
		}
		j++;
	}
}
