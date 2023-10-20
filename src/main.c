/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/20 10:34:11 by yizhang       ########   odam.nl         */
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

t_pixel set_pixel(t_ray ray, int u, int v, uint32_t col)
{
	t_pixel new;
	new.ray = ray;
	new.u = u;
	new.v = v;
	new.col = col;
	return(new);
}

int main(void)
{
	mlx_t* mlx;
	mlx_image_t *img;
	double focal_length = 100.0;
	int viewport_heigh = 1600;
	int viewport_weith = 800;
	
	t_vec camera = set_vec(0,0,0);
	t_vec center = set_vec(0,0,20);
	
	t_vec *viewport;
	t_ray *all_ray;
	t_pixel *all_pix;
	viewport = malloc ((viewport_heigh * viewport_weith) * sizeof(t_vec));
	all_ray = malloc ((viewport_heigh * viewport_weith) * sizeof(t_ray));
	all_pix = malloc ((viewport_heigh * viewport_weith) * sizeof(t_pixel));
	//parse_input(argc, argv);

	mlx = mlx_init(viewport_heigh, viewport_weith, "MiniRT", true);
	img = mlx_new_image(mlx, viewport_heigh, viewport_weith);
	mlx_image_to_window(mlx, img, 0, 0);

	// creat all ray
	// initial all pixel with black
	// if hit sphere than pixel should be white
	int v = 0;
	for(int j = 0; j < viewport_heigh; j++)
	{
		for(int i = 0; i <viewport_weith; i++)
		{
			viewport[v] = set_vec(-viewport_heigh/2+j, viewport_weith/2-i, focal_length);
			all_ray[v] = set_ray(camera, viewport[v]);
			if (hit_sphere(center, 5, all_ray[v]) > 0)
				all_pix[v] = set_pixel(all_ray[v], j, i, 0xFFFFFFFF);
			else
				all_pix[v] = set_pixel(all_ray[v], j, i, 0x000000FF);
			if(v >= viewport_heigh * viewport_weith-2)
				break;
			v++;
		}
	}

	//print image with color
	for(int j = 0; j < viewport_heigh*viewport_weith; j++)
	{
		mlx_put_pixel(img, all_pix[j].u, all_pix[j].v, all_pix[j].col);
	}

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}