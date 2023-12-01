/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/01 16:35:48 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_data(t_data *data)
{
	free(data->objects);
	free(data);
}

void	print_pix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->viewport_w*data->viewport_h)
	{
		mlx_put_pixel(data->img, data->all_pix[i].u, data->all_pix[i].v, data->all_pix[i].col);
		i++;
	}
	mlx_loop(data->mlx);
}

t_data *init(int argc, char **argv)
{
	t_data	*data;
	char	**split_file;

	data = null_check(malloc (1 * sizeof(t_data)));
	data->object_num = 0;
	parse_input(argc, argv, &split_file, data);
	data->viewport_w = 800;
	data->viewport_h = 600;
	data->camera.ratio = 1;
	data->camera.focal_length = data->camera.ratio/tan(data->camera.fov/2) * data->viewport_h/2/tan(data->camera.fov/2);
	data->mlx = mlx_init(data->viewport_w, data->viewport_h, "MiniRT", true);
	data->img = mlx_new_image(data->mlx, data->viewport_w, data->viewport_h);
	data->viewport = malloc ((data->viewport_w * data->viewport_h) * sizeof(t_vec));
	data->all_ray = malloc ((data->viewport_w * data->viewport_h) * sizeof(t_ray));
	init_pix(data);//print all pix to black
	return (data);
}

int main(int argc, char **argv)
{
	t_data	*data;
	int		v;
	int		j;
	int		i;
	
	v = 0;
	j = 0;
	data = init(argc, argv);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	while (j < data->viewport_w)
	{
		i = 0;
		while (i <data->viewport_h)
		{
			data->viewport[v] = set_vec(data->camera.vec.x - data->viewport_w/2 + j, data->camera.vec.y + data->viewport_h/2 - i, data->camera.focal_length);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);
			give_color(data, i, j, v);
			if (v >= data->viewport_w * data->viewport_h-2)
				break;
			v++;
			i++;
		}
		j++;
	}
	print_pix(data);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data->viewport);
	free(data->all_ray);
	free(data->all_pix);
	free_data(data);
	return 0;
}