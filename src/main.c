/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/18 10:13:27 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_vec set_vec(double x, double y, double z)
{
	t_vec new;
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);	
}

t_ray set_ray(t_vec orig, t_vec dir)
{
	t_ray new;
	new.orig = orig;
	new.dir = dir;
	return (new);
}

int main(int argc, char **argv)
{
	mlx_t* mlx;
	mlx_image_t *img;
	double focal_length = 1.0;
	double viewport_heigh = 2.0;
	double viewport_weith = 2.0;
	
	t_vec camera = set_vec(0,0,0);
	
	t_vec viewport_u = set_vec(0,0, focal_length);
	t_vec viewport_v = set_vec(0,0, focal_length);
	
	//parse_input(argc, argv);

	mlx = mlx_init(80, 40, "MiniRT", true);
	img = mlx_new_image(mlx, 80, 40);

	//print image with color
	mlx_image_to_window(mlx, img, 0, 0);
	for(int j = 0; j < 80; j++)
	{
		for(int i = 0; i < 40; i++)
			mlx_put_pixel(img, j, i, 0xFFFFFFFF);
	}

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}