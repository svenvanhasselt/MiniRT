/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/01 16:49:15 by yizhang       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

//x2 + y2 = r2;
//ray = p + tv;

/* a = D|D - (D|V)^2

c = X|X - (X|V)^2 - r^2

b = 2 * (D-V*(D|V))|(X-V*(X|V)) =
 = 2 * (D|X - D|V*(X|V) - X|V*(D|V) + (D|V)*(X|V)) =
 = 2 * (D|X - (D|V)*(X|V)) */

//https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float   a;
    float   b;
    float   c;
    float   discriminant;
    float   z1;
    float   z2;

    //calculate the coefficients for the quadratic equation
   /*  a = dot(ray->dir, ray->dir) - pow(dot(ray->dir, obj->vec2), 2);
    b = 2 * (dot(ray->dir, obj->vec) \
    - dot(ray->dir, obj->vec2) * dot(obj->vec, obj->vec2));
    c = dot(obj->vec, obj->vec) - pow(dot(obj->vec, obj->vec2), 2)-\
    pow(obj->sph_diameter/2, 2); */
    
    a = pow(ray->dir.x, 2) + pow(ray->dir.y, 2);
    b = 2* ray->dir.x * ray->orig.x + 2 * ray->dir.y * ray->orig.y;
    c = ray->orig.x * ray->orig.x + ray->orig.y * ray->orig.y - pow(obj->cyl_diameter/2, 2);
    
    //Calculate the discriminant
    discriminant = b*b - 4*a*c;
    if (discriminant < 0)
       return (false);
    
    //Calculate the two possible t values
    obj->t = (b/2 - sqrt(discriminant)) / a;
    obj->t2 = (b/2 + sqrt(discriminant)) / a;

        
    //Check if the intersection point is within the height on the cylinder
    z1 = ray->orig.z + obj->t * ray->dir.z;
    z2 = ray->orig.z + obj->t2 * ray->dir.z;

    if (obj->t > obj->t2)
        obj->t = obj->t2;

    if ((z1 >= -obj->cyl_height / 2.0 && z1 <= -obj->cyl_height / 2.0) || (z2 >= --obj->cyl_height / 2.0 && z2 <= -obj->cyl_height / 2.0)) 
       return (true);//intersects the cylinder
    return (false);//not intersects
}

//
/* bool    hit_cylinder_cap(t_object *obj, t_ray *ray)
{
    
} */