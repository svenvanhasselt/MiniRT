/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/26 14:35:16 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

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

//Find Intersection Point vector:
//t value, plug it back into the ray equation to find the intersection point:
//	P = O + t*D
//P:intersection
//O:origin
//D:deriction
//reverse inference to derive value
t_vec t_to_vec(float t, t_ray ray)
{
	t_vec	interse;
	interse.x = ray.orig.x + t * ray.dir.x;
	interse.y = ray.orig.y + t * ray.dir.y;
	interse.z = ray.orig.z + t * ray.dir.z;
	return (interse);
}
//
t_color ray_color(t_ray r, float t)
{
	if (t > 0.0)
	{					//the close point on the sphere, and the center of sphere
		t_vec n = unit_vector(sub(t_to_vec(t, r), set_vec(0,0,-1)));
		return set_col(0.5 * (n.x + 1), 0.5 * (n.y + 1), 0.5 * (n.z + 1));//color range base on the unit_vector
	}
	t_vec unit_direction = unit_vector(r.dir);
	float  a = 0.5 * (unit_direction.y + 1.0);
	return (set_col((1.0 - a) + a * 0.5, (1.0 - a) + a * 0.7, (1.0 - a) + a * 1.0));
}
