/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 09:24:23 by yizhang       #+#    #+#                 */
/*   Updated: 2023/11/27 14:28:02 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

bool hit_sphere(t_object *obj, t_ray *r) 
{
	float	radius;

	radius = obj->sph_diameter / 2;
	t_vec oc = sub(r->orig, obj->vec);
	float a = dot(r->dir, r->dir);
	float b = 2.0 * dot(oc, r->dir);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	obj->t = (-b/2 -sqrt(discriminant)) / a;
	if (discriminant < 0 /* || (t <= MINT || t >= MAXT) */)
		return (false);
	else
    	return (true);
	//The intersection of the ray and the sphere results in a quadratic equation of the form:
	//a*t^2 + b*t + c = 0
	//This quadratic equation can have two solutions
	//-b -sqrt(discriminant)
	// indicating that we are solving for the smaller of the two possible values.
}