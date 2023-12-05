/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: yizhang <yizhang@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2023/12/05 12:28:22 by yizhang       ########   odam.nl         */
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

/* static float get_angle(t_vec v1, t_vec v2)
{
    float d;
    float len1;
    float len2;
    float cosine;
    float radians;
    
    d = dot(v1,v2);
    len1 = vec_len(v1);
    len2 = vec_len(v2);

    //Calulate cosine of the angle 
    cosine = d/(len1*len2);
    
    //Calculate the angle in radians
    radians = acos(cosine);
    return (radians);
    
} */

/* static void ray_rotate(t_ray *ray, t_vec vec2)
{
    t_vec rotation_axis;
    t_vec default_dir;
    float angle;
    t_vec norm;

    (void)ray;
    default_dir = set_vec(0,1,0);
    rotation_axis = cross(vec2, default_dir);
    angle = get_angle(vec2, default_dir);
    printf("angle: %f\n",angle);
    norm = unit_vector(rotation_axis);
    //ray->dir = 
    //ray->orig = 

} */

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float   a;
    float   b;
    float   c;
    float   discriminant;
    float   y1;
    float   y2;
    t_vec   oc;
   
    //ray_rotate(ray, obj->vec2);
    // a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
    // b = 2 * (ray->dir.x * ray->orig.x + ray->dir.z * ray->orig.z);
    // c = pow(ray->orig.x, 2) + pow(ray->orig.z, 2) - pow(obj->cyl_diameter/2, 2);

    t_vec norm = obj->vec2;
    
    oc = sub(ray->orig,obj->vec);//subtract the center of the cylinder from the ray origin to turn the problem into a (0,0,0) coordinate
    a = dot(ray->dir,ray->dir) - pow(dot(ray->dir, norm),2);
    b = 2*(dot(ray->dir, oc) - dot(ray->dir, norm) * dot(oc, norm));
    c = dot(oc, oc) - pow(dot(oc, norm), 2) - pow(obj->cyl_diameter/2, 2);
    
    //Calculate the discriminant
    discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        obj->t = -1;
        return (false);
    }
    
    //Calculate the two possible t values
    if (discriminant >= 0)
    {
        obj->t = (-b - sqrt(discriminant)) / (2 * a);
        obj->t2 = (-b + sqrt(discriminant)) /(2 * a);
    }
        
    //Check if the intersection point is within the height on the cylinder
    y1 = ray->orig + obj->t * ray->dir.y;
    y2 = ray->orig - obj->t2 * ray->dir.y;

    if (obj->t > obj->t2)
    {
        float t = obj->t;
        obj->t = obj->t2;
        obj->t2 = t;
    }
    
    if (obj->t < 0)
    {
        obj->t = -1;
        return (false);
    }
    if ((y1 > -obj->cyl_height / 2.0 && y1 < obj->cyl_height / 2.0) || (y2 > -obj->cyl_height / 2.0 && y2 < obj->cyl_height / 2.0)) 
    {
        //printf("y1:%f , y2: %f",y1,y2);
        return (true);//intersects the cylinder
    }
    obj->t = -1;   
    return (true);//not intersects
}

//
/* bool    hit_cylinder_cap(t_object *obj, t_ray *ray)
{
    
} */