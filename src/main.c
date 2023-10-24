/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/24 17:22:31 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdlib.h>

//open window
//give some color
//sending rays into the scene
//vector?
//
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
	return (data);
}
int main(int argc, char **argv)
{
	mlx_t* mlx;
	mlx_image_t *img;
	t_data	*data;

	data = init(argc, argv);

	mlx = mlx_init(1600, 800, "MiniRT", true);
	img = mlx_new_image(mlx, 1600, 800);
	//print image with color
	mlx_image_to_window(mlx, img, 0, 0);
	for(int j = 0; j < 1600; j++)
	{
		for(int i = 0; i < 800; i++)
			mlx_put_pixel(img, j, i, 0xFFFFFFFF);
	}

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	free_data(data);
	return 0;
}