/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: sven <sven@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 16:47:30 by yizhang       #+#    #+#                 */
/*   Updated: 2024/02/02 17:28:22 by svan-has      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

float	hit_cylinder_body(t_object *obj, t_ray *ray)
{
	t_vec	oc;

	oc = sub(ray->orig, obj->vec);
	obj->discrim.a = dot(ray->dir, ray->dir)
		- pow(dot(ray->dir, obj->vec2), 2);
	obj->discrim.b = 2 * (dot(ray->dir, oc)
			- dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
	obj->discrim.c = dot(oc, oc)
		- pow(dot(oc, obj->vec2), 2)
		- pow(obj->diameter / 2, 2);
	obj->discrim.d = discriminant(obj->discrim.a,
			obj->discrim.b, obj->discrim.c);
	calculate_t_and_m(obj, ray);
	return (obj->t);
}

bool	hit_cylinder(t_object *obj, t_ray *ray)
{
	float	t;
	float	t2;

	t = hit_cylinder_caps(obj, ray);
	t2 = hit_cylinder_body(obj, ray);
	obj->t = t2;
	if (obj->t > 0)
		return (true);
	return (false);
}


void calculate_cylinder_bounds(t_object *obj, t_vec *start, t_vec *end)
{
    // Assuming cy->coords is the position of the cylinder, cy->orient is its orientation,
    // and cy->height is its height.

    // Calculate half-height along the y-axis
    float half_height = obj->height / 2.0f;

    // Calculate the direction vectors for the top and bottom of the cylinder
    t_vec top_direction = add(obj->vec, mult_fact(obj->vec2, half_height));
    t_vec bottom_direction = sub(obj->vec, mult_fact(obj->vec2, half_height));

    // Set cy->start and cy->end
    *start = (bottom_direction.y < top_direction.y) ? bottom_direction : top_direction;
    *end = (bottom_direction.y < top_direction.y) ? top_direction : bottom_direction;
}


// float	hit_cylinder_body(t_object *obj, t_ray *ray)
// {
// 	// t_vec	oc;

// 	// oc = sub(ray->orig, obj->vec);
// 	// obj->discrim.a = dot(ray->dir, ray->dir)
// 	// 	- pow(dot(ray->dir, obj->vec2), 2);
// 	// obj->discrim.b = 2 * (dot(ray->dir, oc)
// 	// 		- dot(ray->dir, obj->vec2) * dot(oc, obj->vec2));
// 	// obj->discrim.c = dot(oc, oc)
// 	// 	- pow(dot(oc, obj->vec2), 2)
// 	// 	- pow(obj->diameter / 2, 2);
// 	// obj->discrim.d = discriminant(obj->discrim.a,
// 	// 		obj->discrim.b, obj->discrim.c);
// 	// calculate_t_and_m(obj, ray);
// 	// return (obj->t);

// 	t_vec	q;
// 	t_vec		u;
// 	t_vec		v;

// 	u = cross(ray->dir, obj->vec2);
// 	v = sub(ray->orig, obj->vec);
// 	v = cross(v, obj->vec2);
// 	q.x = dot(u, u);
// 	q.y = 2 * dot(u, v);
// 	float r2 = obj->diameter * obj->diameter * 0.25;
// 	q.z = dot(v, v) - r2;

// 	float delta = q.y * q.y - 4 * q.x * q.z;
// 	if (delta < 0)
// 		return (-1);
// 	float t1 = (-q.y - sqrt(delta)) / (q.x * 2);
// 	float t2 = (-q.y + sqrt(delta)) / (q.x * 2);

	
// 	if (t2 <= 0.0001 && t1 <= 0.0001)
// 		return (-1);
// 	if (t1 <= 0.0001 || (t2 > 0.0001 && (t2 < t1)))
// 		t1 = t2;
	
// 	obj->t = t1;
// 	t_vec *start = malloc (1 * sizeof(t_vec));
// 	t_vec *end = malloc (1 * sizeof(t_vec));
// 	t_vec hitpoint = calc_hitpoint(*ray, obj->t );
// 	printf("%f\n", end->x);
// 	calculate_cylinder_bounds(obj, start, end);
// 	printf("n: %f %f\n", start->y, hitpoint.y);


// 	if (hitpoint.y >= start->y && hitpoint.y <= end->y)
//         return (obj->t);
// 	else
// 		return (-1); // The intersection point is within the height of the cylinder

// 	// if (pow(vec_len(sub(obj->vec2, calc_hitpoint(*ray, t1))), 2) <= pow(obj->height * 0.5, 2) + r2)
// 	// {
// 	// 	obj->t = t1;
// 	// 	// ray->t = t1;
// 	// }
// 	// else
// 	// 	obj->t = -1;

// 	// obj->m1 = dot(ray->dir, obj->vec2) * obj->t
// 	// 	+ dot(sub(ray->orig, obj->vec), obj->vec2);
// 	// obj->m2 = dot(ray->dir, obj->vec2) * obj->t2
// 	// 	+ dot(sub(ray->orig, obj->vec), obj->vec2);
// 	// // obj->t = compare_t(obj->t, obj->t2);
// 	// if ((obj->m1 <= obj->height / 2 && obj->m1 >= -obj->height / 2)
// 	// 	|| (obj->m2 <= obj->height / 2 && obj->m2 >= -obj->height / 2))
// 	// {
// 	// 	if (obj->m1 <= obj->height / 2 && obj->m1 >= -obj->height / 2)
// 	// 		obj->inside = false;
// 	// 	else
// 	// 		obj->inside = true;
// 	// 	return (obj->t);
// 	// }
// 	// obj->t = -1;
// 	return (obj->t);
// 	// ray_mul(&hit->phit, r, q.t1);
// 	// v = vect_sub(cy->coords, hit->phit);
// 	// hit->nhit = cross_prod(v, cy->orient);
// 	// hit->nhit = cross_prod(hit->nhit, cy->orient);
// 	// normalize(&hit->nhit);
// 	// if (dot_prod(hit->nhit, r->dir))
// 	// 	hit->nhit = vect_inv(hit->nhit);
// 	// return (TRUE);
// }