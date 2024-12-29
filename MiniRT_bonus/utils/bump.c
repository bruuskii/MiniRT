// // Example function to retrieve a bump map "height" from UV coordinates
// // In a real application, this might sample from an image or procedural noise
// float get_bump_value(float u, float v) 
// {
//     return 0.1f * sinf(10.0f * u) * cosf(10.0f * v);
// }

// Vector apply_bump_mapping(Vector normal_in, Vector tangent, Vector bitangent,
//                           float u, float v) 
// {
//     // Get the bump intensity from the bump map
//     float bump_value = get_bump_value(u, v);

//     // Adjust how strongly the bump map influences the normal
//     float bump_strength = 0.5f;  // you can tweak this

//     // Perturb the normal in tangent space
//     // new_normal = normal_in + bump_value*(tangent + bitangent)
//     // But better is to handle each axis properly. For simplicity:
//     Vector bump_vector = vector_add(tangent, bitangent);
//     bump_vector = vector_scale(bump_vector, bump_value * bump_strength);

//     // Add the bump to the base normal
//     Vector bumped_normal = vector_add(normal_in, bump_vector);

//     // Re-normalize after perturbation
//     bumped_normal = vector_normalize(bumped_normal);

//     return bumped_normal;
// }

// int main(void) 
// {
//     // Suppose we have these values from our intersection calculations:
//     Vector normal_in   = {0, 1, 0};   // Upward facing normal
//     Vector tangent     = {1, 0, 0};   // Tangent in the X direction
//     Vector bitangent   = {0, 0, 1};   // Bitangent in the Z direction
//     float u = 0.3f;  // example U coordinate in range [0..1]
//     float v = 0.4f;  // example V coordinate in range [0..1]

//     // Apply the bump mapping
//     Vector bumped_normal = apply_bump_mapping(normal_in, tangent, bitangent, u, v);

//     printf("Bumped Normal: (%f, %f, %f)\n",
//             bumped_normal.x, bumped_normal.y, bumped_normal.z);

//     return 0;
// }