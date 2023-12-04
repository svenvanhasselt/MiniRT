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

// static void ray_rotate(t_ray *ray, t_vec dir)
// {
//     t_vec rotation_axis;
//     t_vec default_dir;
//     float angle;

//     default_dir = set_vec(0,1,0);
//     rotation_axis = cross(dir, default_dir);


// }

// int rayCylinderIntersect(double x0, double y0, double z0,
//                           double dx, double dy, double dz) {
//     // Calculate the coefficients for the quadratic equation
//     double a = ray->dir.x * dx + dy * dy - (dx * axisX + dy * axisY) * (dx * axisX + dy * axisY);
//     double b = 2.0 * ((x0 - cx - axisX * (x0 - cx) - axisY * (y0 - cy)) * dx
//                       + (y0 - cy - axisX * (x0 - cx) - axisY * (y0 - cy)) * dy
//                       - (x0 - cx - axisX * (x0 - cx) - axisY * (y0 - cy)) * (dx * axisX + dy * axisY));
//     double c = (x0 - cx - axisX * (x0 - cx) - axisY * (y0 - cy)) * (x0 - cx - axisX * (x0 - cx) - axisY * (x0 - cx))
//               + (y0 - cy - axisX * (x0 - cx) - axisY * (y0 - cy)) * (y0 - cy - axisX * (x0 - cx) - axisY * (y0 - cy))
//               - (diameter / 2.0) * (diameter / 2.0);
    
// }

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float   a;
    float   b;
    float   c;
    float   discriminant;
    float   y1;
    float   y2;
   // t_vec   oc;

    /* a = ray->dir.x * ray->dir.x + ray->dir.y * ray->dir.y - (ray->dir.x * obj->vec2.x + ray->dir.y * obj->vec2.y) * (ray->dir.x * obj->vec2.x + ray->dir.y * obj->vec2.y);
    b = 2.0 * ((ray->orig.x - obj->vec.x - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y )) * ray->dir.x\
                      + (ray->orig.y - obj->vec.y - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y)) * ray->dir.y\
                      - (ray->orig.x - obj->vec.x - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y)) * (ray->dir.x * obj->vec2.x + ray->dir.y * obj->vec2.y));
    c = (ray->orig.x - obj->vec.x - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y)) * (ray->orig.x - obj->vec.x - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.x - obj->vec.x))\
              + (ray->orig.y - obj->vec.y - obj->vec2.x * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y)) * (ray->orig.y - obj->vec.y - obj->vec2.y * (ray->orig.x - obj->vec.x) - obj->vec2.y * (ray->orig.y - obj->vec.y))\
              - (obj->cyl_diameter / 2.0) * (obj->cyl_diameter / 2.0); */

    //calculate the coefficients for the quadratic equation
    //rotate the ray.
    a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2);
    b = 2 * (ray->dir.x * ray->orig.x + ray->dir.z * ray->orig.z);
    c = pow(ray->orig.x, 2) + pow(ray->orig.z, 2) - pow(obj->cyl_diameter/2, 2);
    
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
    y1 = ray->orig.y + obj->t * ray->dir.y;
    y2 = ray->orig.y + obj->t2 * ray->dir.y;

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
    return (false);//not intersects
}

//
/* bool    hit_cylinder_cap(t_object *obj, t_ray *ray)
{
    
} */