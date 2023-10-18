/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/18 11:52:38 by yizhang       ########   odam.nl         */
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

t_pixel set_pixel(t_ray ray, int x, int y)
{
	t_pixel new;
	new.ray = ray;
	new.x = x;
	new.y = y;
	return(new);
}

int main(void)
{
	mlx_t* mlx;
	mlx_image_t *img;
	double focal_length = 1.0;
	//double viewport_heigh = 80.0;
	//double viewport_weith = 40.0;
	
	t_vec camera = set_vec(0,0,0);
	
	t_vec viewport[80 * 40]; 
	t_ray all_ray[80 * 40];
	t_pixel all_pix[80*40];
	//parse_input(argc, argv);

	mlx = mlx_init(80, 40, "MiniRT", true);
	img = mlx_new_image(mlx, 80, 40);
	mlx_image_to_window(mlx, img, 0, 0);

	//creat all ray
	int v = 0;
	for(int j = 0; j < 80; j++)
	{
		for(int i = 0; i < 40; i++)
		{
			viewport[v] = set_vec(-40+j, 20-i, focal_length);
			all_ray[v] = set_ray(camera, viewport[v]);
			all_pix[v] = set_pixel(all_ray[v], j, i);
			v++;
		}
	}

	//print image with color
	for(int j = 0; j < 80*40; j++)
	{
		mlx_put_pixel(img, all_pix[j].x, all_pix[j].y, 0xFFFFFFFF);
	}

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}