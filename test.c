#include <stdio.h>
#include <math.h>

typedef struct {
    float x, y, z;
} Vector3;

Vector3 scale(Vector3 v, float c) {
    Vector3 result;
    result.x = v.x * c;
    result.y = v.y * c;
    result.z = v.z * c;
    return result;
}


// Define a structure to represent a ray
typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

// Define a structure to represent a sphere
typedef struct {
    Vector3 center;
    float radius;
} Sphere;

// Define a structure to represent a light source
typedef struct {
    Vector3 position;
    float intensity;
} Light;

// Function to compute the dot product of two vectors
float dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Function to subtract two vectors
Vector3 subtract(Vector3 a, Vector3 b) {
    Vector3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

// Function to normalize a vector
Vector3 normalize(Vector3 v) {
    float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    Vector3 result;
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}

// Function to check if a ray intersects with a sphere
int intersect(Ray ray, Sphere sphere, float *t) {
    Vector3 oc = subtract(ray.origin, sphere.center);
    float a = dot(ray.direction, ray.direction);
    float b = 2.0 * dot(oc, ray.direction);
    float c = dot(oc, oc) - sphere.radius * sphere.radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        // No intersection
        return 0;
    }

    // Compute the closest intersection point
    *t = (-b - sqrt(discriminant)) / (2.0 * a);
    return 1;
}


// Function to compute the color of a pixel using the Phong reflection model
Vector3 shade(Ray ray, Sphere sphere, Light light) {
    // Find the intersection point
    float t;
    if (!intersect(ray, sphere, &t)) {
        // No intersection, return background color
        return (Vector3){0, 0, 0};
    }

    // Compute the intersection point
    Vector3 intersection_point = {
        ray.origin.x + t * ray.direction.x,
        ray.origin.y + t * ray.direction.y,
        ray.origin.z + t * ray.direction.z
    };

    // Compute the normal at the intersection point
    Vector3 normal = subtract(intersection_point, sphere.center);
    normal = normalize(normal);

    // Compute the direction to the light source
    Vector3 to_light = subtract(light.position, intersection_point);
    to_light = normalize(to_light);

    // Compute the reflection vector
    Vector3 reflection = subtract(normal, scale(to_light, 2.0 * dot(normal, to_light)));

    // Compute the diffuse and specular components using the Phong model
    float diffuse = fmax(0, dot(normal, to_light));
    float specular = pow(fmax(0, dot(reflection, ray.direction)), 16);

    // Combine the ambient, diffuse, and specular components
    float ambient = 0.1; // Ambient component
    Vector3 color = {
        ambient + light.intensity * diffuse,
        ambient + light.intensity * specular,
        ambient + light.intensity * specular
    };

    return color;
}

int main() {
    // Define the scene
    Sphere sphere = {{0, 0, -5}, 1.0}; // Sphere at the center with radius 1
    Light light = {{1, 2, -3}, 1.0}; // Light source at (1, 2, -3) with intensity 1.0

    // Define the image size
    int width = 800;
    int height = 600;

    // Define the camera parameters
    Vector3 camera_position = {0, 0, 0};
    float fov = M_PI / 2.0; // Field of view

    // Create an image buffer
    unsigned char image[width][height][3];

    // Ray tracing loop
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Compute the ray direction for the current pixel
            float aspect_ratio = (float)width / height;
            float px = (2.0 * (x + 0.5) / width - 1.0) * tan(fov / 2.0) * aspect_ratio;
            float py = (1.0 - 2.0 * (y + 0.5) / height) * tan(fov / 2.0);
            Vector3 ray_direction = normalize((Vector3){px, py, -1});

            // Create the ray
            Ray ray = {camera_position, ray_direction};

            // Compute the color of the pixel
            Vector3 color = shade(ray, sphere, light);

            // Clamp the color values to [0, 1]
            color.x = fmin(1.0, fmax(0.0, color.x));
            color.y = fmin(1.0, fmax(0.0, color.y));
            color.z = fmin(1.0, fmax(0.0, color.z));

            // Store the color in the image buffer
            image[x][y][0] = (unsigned char)(color.x * 255);
            image[x][y][1] = (unsigned char)(color.y * 255);
            image[x][y][2] = (unsigned char)(color.z * 255);
        }
    }

    // Output the image to a PPM file
    FILE *output_file = fopen("output.ppm", "wb");
    fprintf(output_file, "P6\n%d %d\n255\n", width, height);
    fwrite(image, sizeof(unsigned char), 3 * width * height, output_file);
    fclose(output_file);

    return 0;
}
