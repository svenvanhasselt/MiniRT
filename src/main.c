/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 17:46:14 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/25 15:16:11 by yizhang       ########   odam.nl         */
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

t_color set_col(double r, double g, double b)
{
	t_color new;
	new.r = r;
	new.g = g;
	new.b = b;
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
	//what is FOV and 3d normalized orientation vector in vector?
	//how to caculate the focal_len?
	mlx_t* mlx;
	mlx_image_t *img;
	double focal_length = 500;
	int viewport_high = 1600;
	int viewport_weith = 800;
	
	t_vec camera = set_vec(0,0,0);
	t_vec center = set_vec(0,0,20);
	//t_vec center2 = set_vec(10,0,20);
	
	t_vec *viewport;
	t_ray *all_ray;
	t_pixel *all_pix;
	viewport = malloc ((viewport_high * viewport_weith) * sizeof(t_vec));
	all_ray = malloc ((viewport_high * viewport_weith) * sizeof(t_ray));
	all_pix = malloc ((viewport_high * viewport_weith) * sizeof(t_pixel));
	//parse_input(argc, argv);

	mlx = mlx_init(viewport_high, viewport_weith, "MiniRT", true);
	img = mlx_new_image(mlx, viewport_high, viewport_weith);
	mlx_image_to_window(mlx, img, 0, 0);

	// creat all ray
	// initial all pixel with black
	// if hit sphere than pixel should be other color
	int v = 0;
	for(int j = 0; j < viewport_high; j++)
	{
		for(int i = 0; i <viewport_weith; i++)
		{
			viewport[v] = set_vec(-viewport_high/2+j, viewport_weith/2-i, focal_length);
			all_ray[v] = set_ray(camera, viewport[v]);
			double t = hit_sphere(center, 12.6/2, all_ray[v]);
			if (t > 0)
			{
				t_color color = ray_color(all_ray[v],t);
				all_pix[v] = set_pixel(all_ray[v], j, i, get_rgba(color.r * 255, color.g *255, color.b *255, 255));//account the lenth 
			}
			else
				all_pix[v] = set_pixel(all_ray[v], j, i, get_rgba(0, 0, 0, 255));
			if(v >= viewport_high * viewport_weith-2)
				break;
			//else if (hit_sphere(center, 12.6/2, all_ray[v]) > 0)
			//	all_pix[v] = set_pixel(all_ray[v], j, i, get_rgba(10, 0, 255, 255));//account the lenth 
			v++;
		}
	}
	//Front faces versus back faces
	//A List of Hittable Objects
	
	//print image with color
	for(int j = 0; j < viewport_high*viewport_weith; j++)
	{
		mlx_put_pixel(img, all_pix[j].u, all_pix[j].v, all_pix[j].col);
	}

	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return 0;
}