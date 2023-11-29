/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/29 16:53:36 by svan-has      ########   odam.nl         */
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
	data->viewport_w = 800;
	data->viewport_h = 600;
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
	
	data = init(argc, argv);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	float fov = 45;
	float ratio = 1;
	float focal_length = ratio/tan(fov/2) * data->viewport_h/2/tan(fov/2);
	printf("lenth: %f\n",focal_length);

	int v = 0;
	
	for(int j = 0; j < data->viewport_w; j++)
	{
		for(int i = 0; i <data->viewport_h; i++)
		{
			data->viewport[v] = set_vec(data->camera.vec.x - data->viewport_w/2 + j, data->camera.vec.y + data->viewport_h/2 - i, focal_length);
			data->all_ray[v] = set_ray(data->camera.vec, data->viewport[v]);
			hit_object(data, v);//plane... lenth,order
			give_color(data, i, j, v);// try ray norm
			if(v >= data->viewport_w * data->viewport_h-2)
				break;
			v++;
		}
	}
	
	//print image with color
	for(int j = 0; j < data->viewport_w*data->viewport_h; j++)
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