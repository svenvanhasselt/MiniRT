/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/27 17:38:56 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//make a object list
// bool	hit_object(t_ray ray, t_object *obj,int weith, int high, t_pixel pix)
// {
// 	int i;
// 	float t;
// 	i = 0;
// 	while(obj[i])
// 	{
// 		if (obj[i].type == sphere)
// 		{
// 			t = hit_sphere(obj[i].vec, obj[i].sph_diameter/2, ray);
// 			give_color(ray, t, weith, high, pix, obj[i]);
// 		}
// 		else if (obj[i].type == plane /* && hit_plane */)
// 			return (true);
// 		else if (obj[i].type == cylinder /* && hit_cylinder */)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// void give_color(t_ray ray, float t, int weith, int high, t_pixel pix, t_object obj)
// {
// 	if (t > 0.0)
// 	{
// 		t_color color = ray_color(ray,t,obj.vec, obj);//compute the norm of object and color
// 		pix = set_pixel(ray, high, weith, get_rgba(color.r, color.g, color.b, 255));
// 	}
// 	else
// 		pix = set_pixel(ray, high, weith, get_rgba(0, 0, 0, 255));
	
// }

t_vec	set_facenorm(t_vec ray_dir, t_vec face)//calculate if the ray hit the outside of sphere
{
	if (dot(ray_dir, face) > 0.0)//ray hit inside of sphere
		return (set_vec(-face.x, -face.y, -face.z));// face = -face
	else
		return (face);
}
