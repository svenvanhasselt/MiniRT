/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 16:18:25 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

//make a object list
bool	hit_object(t_data *data, int v)
{
	int i;

	i = 0;
	while (i < data->object_num)
	{
		if (data->objects[i].type == sphere)
			hit_sphere(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == plane)
			hit_plane(&data->objects[i], &data->all_ray[v]);
		else if (i == 3)
			hit_cylinder(&data->objects[i], &data->all_ray[v]);
		i++;
	}
	return (false);
}

void give_color(t_data *data, int weith, int high, int v)
{
	int i;

	i = 0;
	while (i < data->object_num)
	{
		if (data->objects[i].t > 0.0)
		{
			t_color color = ray_color(data->all_ray[v], data->objects[i].t, data->objects[i], data);
			data->all_pix[v] = set_pixel(data->all_ray[v], high, weith, get_rgba(color.r, color.g, color.b, 255));
		}
		i++;
	}
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
	i = 0;
	data->all_pix = malloc ((data->viewport_w * data->viewport_h) * sizeof(t_pixel));
	while (j < data->viewport_w)
	{
		while (i <data->viewport_h)
		{
			data->all_pix[v] = set_pixel(data->all_ray[v], j, i, get_rgba(0, 0, 0, 255));
			v++;
			i++;
		}
		j++;
	}
}
