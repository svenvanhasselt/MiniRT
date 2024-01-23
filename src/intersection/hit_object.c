/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/23 17:46:36 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

bool	hit_object(t_data *data, int v)
{
	int	i;

	i = 0;
	data->all_ray[v].t = -1;
	data->all_ray[v].inside = false;
	while (i < data->object_num)
	{
		if (data->objects[i].type == sphere
			&& hit_sphere(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == plane
			&& hit_plane(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == cylinder
			&& hit_cylinder(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		else if (data->objects[i].type == cone
			&& hit_cone(&data->objects[i], &data->all_ray[v]))
			compare_update_t(&data->objects[i], &data->all_ray[v]);
		i++;
	}
	return (false);
}

void	init_pix(t_data *data)
{
	int	v;
	int	j;
	int	i;

	v = 0;
	j = 0;
	data->all_pix = malloc ((data->viewport_w
				* data->viewport_h) * sizeof(t_pixel));
	while (j < data->viewport_w)
	{
		i = 0;
		while (i < data->viewport_h)
		{
			data->all_pix[v] = set_pixel(data->all_ray[v], j, i, 255);
			v++;
			i++;
		}
		j++;
	}
}
