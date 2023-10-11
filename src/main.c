/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/10 13:55:26 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//open window
//give some color
//sending rays into the scene
//vector?
//

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	mlx_t* mlx;
	mlx_image_t *img;

	mlx = mlx_init(1600, 800, "MiniRT", true);
	img = mlx_new_image(mlx, 1000, 600);
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
	return 0;
}