/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/10 12:33:15 by yizhang       ########   odam.nl         */
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
	img = mlx_new_image(mlx,1000,600);
	
	long int color = get_rgba(0, 255, 0, 1);
		printf("%li\n", color);
	//print image with color
	mlx_image_to_window(mlx, img, 0, 0);
	for(int j = 0; j < 600; j++)
	{
		for(int i = 0; i < 600; i++)
			mlx_put_pixel(img, j, i, 0xFFFF00FF);
	}

	mlx_loop(mlx);
	//clean everything
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}