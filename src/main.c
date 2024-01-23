/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2024/01/23 17:30:41 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include "../lib/libft/includes/libft.h"

void	free_data(t_data *data)
{
	free(data->objects);
	free(data);
}

void	print_pix(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->ray_pix_num)
	{
		mlx_put_pixel(data->img, data->all_pix[i].u,
			data->all_pix[i].v, data->all_pix[i].col);
		i++;
	}
	mlx_put_string(data->mlx,
		"Rotation: 'R' | Translation: 'T'| Moving: 'A'+'D', 'S'+'W', 'Q'+'E'",
		0, data->viewport_h + 25);
	mlx_put_string(data->mlx,
		"Select objects: 'O' | Camera: 'A' | Light: 'L'",
		0, data->viewport_h);
}

void	init_rotation(t_data *data)
{
	int	i;

	data->rotation.action = translate_object;
	data->rotation.object = &data->objects[0];
	data->rotation.obj_type = object;
	i = 0;
	while (i < data->object_num)
	{
		data->objects[i].gamma = 0;
		data->objects[i].alpha = 0;
		data->objects[i].beta = 0;
		i++;
	}
}

t_data	*init(int argc, char **argv)
{
	t_data	*data;
	char	**split_file;

	data = null_check(malloc (1 * sizeof(t_data)));
	data->object_num = 0;
	parse_input(argc, argv, &split_file, data);
	if (!data->viewport_w || !data->viewport_h)
	{
		data->viewport_w = 800;
		data->viewport_h = 600;
	}
	data->camera.focal_length = 2 * (data->viewport_h * tanf
			(data->camera.fov / 2 / 180 * 3.1415926));
	data->mlx = mlx_init(data->viewport_w,
			data->viewport_h + 50, "MiniRT", true);
	data->img = mlx_new_image(data->mlx, data->viewport_w, data->viewport_h);
	data->ray_pix_num = data->viewport_w * data->viewport_h;
	data->viewport = malloc (data->ray_pix_num * sizeof(t_vec));
	data->all_ray = malloc (data->ray_pix_num * sizeof(t_ray));
	init_rotation(data);
	init_pix(data);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = init(argc, argv);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	calc_viewport(data);
	print_pix(data);
	mlx_key_hook(data->mlx, &key_press, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	free(data->viewport);
	free(data->all_ray);
	free(data->all_pix);
	free_data(data);
	return (0);
}
