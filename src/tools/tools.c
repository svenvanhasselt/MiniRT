/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: svan-has <svan-has@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/26 10:53:12 by svan-has      #+#    #+#                 */
/*   Updated: 2024/01/26 15:02:57 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	add_color(t_data *data, int i, int j, int v)
{
	t_vec	color;

	if (data->all_ray[v].t > 0)
	{
		color = ray_color(data->all_ray[v], data->all_ray[v].t, \
		data->all_ray[v].obj, data);
		data->all_pix[v] = set_pixel(data->all_ray[v], j, i, \
		get_rgba(color.x, color.y, color.z));
	}
}

void	calc_viewport(t_data *data)
{
	int		v;
	int		j;
	int		i;

	v = 0;
	j = 0;
	while (j < data->viewport_w)
	{
		i = 0;
		while (i < data->viewport_h)
		{
			data->viewport[v] = init_camera(data, j, i);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);
			add_color(data, i, j, v);
			if (v >= data->ray_pix_num)
				break ;
			v++;
			i++;
		}
		j++;
	}
}

void	print_message(t_data *data, char *message)
{
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->viewport_w, data->viewport_h);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	print_pix(data);
	mlx_put_string(data->mlx, message, 0, 0);
}
