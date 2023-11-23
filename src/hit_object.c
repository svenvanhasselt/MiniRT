/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_object.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/26 13:43:59 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/23 16:02:43 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//make a object list
bool	hit_object(t_ray ray, t_object *obj,int weith, int high, t_pixel pix)
{
	int i;
	int t;
	i = 0;
	while(i < 2)
	{
		if (obj[i].type == sphere)
		{
			t = hit_sphere(obj[i].vec, obj[i].sph_diameter/2, ray);
			give_color(ray, t, weith, high, pix, obj[i]);
		}
		else if (obj[i].type == plane /* && hit_plane */)
			return (true);
		else if (obj[i].type == cylinder /* && hit_cylinder */)
			return (true);
		i++;
	}
	return (false);
}

void give_color(t_ray ray, float t, int weith, int high, t_pixel pix, t_object obj)
{
	if (t > 0.0)
	{
		t_color color = ray_color(ray,t,obj.vec);//compute the norm of object and color
		pix = set_pixel(ray, high, weith, get_rgba(color.r * 255, color.g * 255, color.b * 255, 255));
	}
	else
		pix = set_pixel(ray, high, weith, get_rgba(0, 0, 0, 255));
	
}
	//1. The equation for a sphere of radius r:
	//	x^2+y^2+z^2 = r^2
	//if a given point P(x,y,z)
	
	//on the sphere, then x2+y2+z2 = r2
	//inside the sphere, then x2+y2+z2 < r2
	//outside the sphere, then x2+y2+z2 > r2

	//2. If we want to allow the sphere center to be at an arbitrary point (Cx,Cy,Cz);
	//	(Px−Cx)^2+(Py−Cy)^2+(Pz−Cz)^2 = r^2

	//3.The vector from center C to P is (P - C)
	//	(P−C)⋅(P−C) = (x−Cx)^2+(y−Cy)^2+(z−Cz)^2

	//4. (P−C)⋅(P−C) = r^2
	//	sub(P, C)*sub(P, C)-> Multipliction of Vectors - dot product and cross product.
	
	//if our ray P(t)=A+tb
	
 	//ever hits the sphere anywhere.
	//	(P(t)−C)⋅(P(t)−C)=r^2
	//	((A+tb)−C)⋅((A+tb)−C)=r^2
	//	t2b⋅b + 2tb⋅(A−C) + (A−C)⋅(A−C)−r^2=0

	//A = b*b 
	//B = b⋅(A−C)
	//C = (A−C)⋅(A−C)−r^2
	//quadratic equation : at^2 + bt + c = 0
	//{t1,t2} = (-b±√(b²-4ac))/(2a) 
	//The discriminant is the part of the quadratic formula underneath the square root symbol: b²-4ac
	//If  b2−4ac<0
	//then there are no real roots for the quadratic equation.
	//If  b2−4ac=0
	//then the quadratic equation has two real, identical roots.
	//If  b2−4ac>0
	//then the quadratic equation has two real, distinct roots
	
float hit_sphere(t_vec center, float radius, t_ray r) 
{
	t_vec oc = sub(r.orig, center);
	float a = dot(r.dir, r.dir);
	float b = 2.0 * dot(oc, r.dir);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	float	t = (-b/2 -sqrt(discriminant)) / a;
	if (discriminant < 0 /* || (t <= MINT || t >= MAXT) */)
		return (-1);
	else
    	return (t);
	//The intersection of the ray and the sphere results in a quadratic equation of the form:
	//a*t^2 + b*t + c = 0
	//This quadratic equation can have two solutions
	//-b -sqrt(discriminant)
	// indicating that we are solving for the smaller of the two possible values.
}

t_vec	set_facenorm(t_vec ray_dir, t_vec face)//calculate if the ray hit the outside of sphere
{
	if (dot(ray_dir, face) > 0.0)//ray hit inside of sphere
		return (set_vec(-face.x, -face.y, -face.z));// face = -face
	else
		return (face);
}
