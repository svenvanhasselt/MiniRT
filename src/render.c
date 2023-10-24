/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 17:47:22 by yizhang       #+#    #+#                 */
/*   Updated: 2023/10/24 12:11:19 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	
double hit_sphere(t_vec center, float radius, t_ray r) 
{
	t_vec oc = sub(r.orig, center);
	double a = dot(r.dir, r.dir);
	double b = 2.0 * dot(oc, r.dir);
	double c = dot(oc, oc) - radius*radius;
	double discriminant = b*b - 4*a*c;
    return (discriminant);
}

//next step: find the nearest root that lies in the acceptable range
	nearest()
{
		
}