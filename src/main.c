/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/27 15:09:23 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_data(t_data *data)
{
	free(data->objects);
	free(data);
}

t_data *init(int argc, char **argv)
{
	t_data	*data;
	char	**split_file;

	data = null_check(malloc (1 * sizeof(t_data)));
	data->object_num = 0;
	parse_input(argc, argv, &split_file, data);
	data->viewport_high = 1600;
	data->viewport_weith = 800;
	data->mlx = mlx_init(data->viewport_high, data->viewport_weith, "MiniRT", true);
	data->img = mlx_new_image(data->mlx, data->viewport_high, data->viewport_weith);
	data->viewport = malloc ((data->viewport_high * data->viewport_weith) * sizeof(t_vec));
	data->all_ray = malloc ((data->viewport_high * data->viewport_weith) * sizeof(t_ray));
	data->all_pix = malloc ((data->viewport_high * data->viewport_weith) * sizeof(t_pixel));
	init_pix(data);//print all pix to black
	return (data);
}

int main(int argc, char **argv)
{
	t_data	*data;
	
	float focal_length = 500;

	data = init(argc, argv);
	mlx_image_to_window(data->mlx, data->img, 0, 0);

	int v = 0;
	
	for(int j = 0; j < data->viewport_high; j++)
	{
		for(int i = 0; i <data->viewport_weith; i++)
		{
			data->viewport[v] = set_vec(data->viewport_high*-1/2+j, data->viewport_weith/2-i, focal_length);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);
			give_color(data, i, j, v);
			if(v >= data->viewport_high * data->viewport_weith-2)
				break;
			v++;
		}
	}
	
	//print image with color
	for(int j = 0; j < data->viewport_high*data->viewport_weith; j++)
	{
		mlx_put_pixel(data->img, data->all_pix[j].u, data->all_pix[j].v, data->all_pix[j].col);
	}
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data->viewport);
	free(data->all_ray);
	free(data->all_pix);
	free_data(data);
	return 0;
}