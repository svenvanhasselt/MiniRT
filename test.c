#include <stdbool.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    float x, y, z;
} t_vec;

typedef struct {
    t_vec center;
    t_vec axis;
    float radius;
} t_cylinder;

bool is_point_inside_cylinder(t_vec point, t_cylinder cylinder) {
    // Calculate the vector from the cylinder center to the point
    t_vec center_to_point = {point.x - cylinder.center.x, point.y - cylinder.center.y, point.z - cylinder.center.z};

    // Calculate the projection of center_to_point onto the cylinder axis
    float projection = center_to_point.x * cylinder.axis.x + center_to_point.y * cylinder.axis.y + center_to_point.z * cylinder.axis.z;
    t_vec projected_point = {
        cylinder.center.x + projection * cylinder.axis.x,
        cylinder.center.y + projection * cylinder.axis.y,
        cylinder.center.z + projection * cylinder.axis.z
    };

    // Calculate the distance between the point and its projection onto the axis
    float distance_to_axis = sqrt((point.x - projected_point.x) * (point.x - projected_point.x) +
                                  (point.y - projected_point.y) * (point.y - projected_point.y) +
                                  (point.z - projected_point.z) * (point.z - projected_point.z));

    // Check if the distance is less than or equal to the radius
    return distance_to_axis <= cylinder.radius;
}

int main() {
    // Example usage
    t_cylinder cylinder = {{0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, 1.0};
    t_vec inside_point = {0.5, 0.5, 0.5};
    t_vec outside_point = {2.0, 2.0, 2.0};

    if (is_point_inside_cylinder(inside_point, cylinder)) {
        printf("The point is inside the cylinder.\n");
    } else {
        printf("The point is outside the cylinder.\n");
    }

    if (is_point_inside_cylinder(outside_point, cylinder)) {
        printf("The point is inside the cylinder.\n");
    } else {
        printf("The point is outside the cylinder.\n");
    }

    return 0;
}
