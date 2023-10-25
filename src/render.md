# Ray-Sphere Intersection Calculation

This document outlines the process of calculating the intersection point between a ray and a sphere in a 3D space using C language.

## 1. Mathematical Background

### Ray Equation:
A ray in 3D space is represented by the equation:
\[ \mathbf{P}(t) = \mathbf{O} + t \cdot \mathbf{D} \]
where:
- \( \mathbf{P}(t) \) is a point on the ray at parameter \( t \),
- \( \mathbf{O} \) is the origin of the ray,
- \( \mathbf{D} \) is the direction of the ray,
- \( t \) is a scalar parameter.

### Sphere Equation:
A sphere in 3D space is represented by the equation:
\[ (\mathbf{P} - \mathbf{C}) \cdot (\mathbf{P} - \mathbf{C}) - r^2 = 0 \]
where:
- \( \mathbf{C} \) is the center of the sphere,
- \( r \) is the radius of the sphere.

### Intersection Equation:
Substituting the ray equation into the sphere equation and simplifying, we get a quadratic equation in terms of \( t \):
\[ a \cdot t^2 + b \cdot t + c = 0 \]
with the coefficients defined as:
- \( a = \mathbf{D} \cdot \mathbf{D} \)
- \( b = 2 \cdot (\mathbf{O} - \mathbf{C}) \cdot \mathbf{D} \)
- \( c = (\mathbf{O} - \mathbf{C}) \cdot (\mathbf{O} - \mathbf{C}) - r^2 \)

The discriminant of this quadratic equation is calculated as:
\[ \text{discriminant} = b^2 - 4 \cdot a \cdot c \]

## 2. C Code Implementation

Below is a C code snippet that implements the above mathematical framework to find the nearest intersection point of a ray and a sphere:

```c
typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

typedef struct {
    Vector3 center;
    float radius;
} Sphere;

Vector3 raySphereIntersection(Ray ray, Sphere sphere) {
    Vector3 oc = {ray.origin.x - sphere.center.x,
                  ray.origin.y - sphere.center.y,
                  ray.origin.z - sphere.center.z};

    float a = ray.direction.x * ray.direction.x +
              ray.direction.y * ray.direction.y +
              ray.direction.z * ray.direction.z;
    float b = 2.0f * (oc.x * ray.direction.x +
                      oc.y * ray.direction.y +
                      oc.z * ray.direction.z);
    float c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // No intersection
        return (Vector3){0, 0, 0};  // Return a specific value to indicate no intersection
    } else {
        float t = (-b - sqrt(discriminant)) / (2.0f * a);
        Vector3 intersectionPoint = {ray.origin.x + t * ray.direction.x,
                                     ray.origin.y + t * ray.direction.y,
                                     ray.origin.z + t * ray.direction.z};
        return intersectionPoint;
    }
}
