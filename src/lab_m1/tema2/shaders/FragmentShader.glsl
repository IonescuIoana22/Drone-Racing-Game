#version 330

// Input
in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_color;
in float noise_val;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // Define colors for terrain
    vec3 grass_color = vec3(0.54, 0.27, 0.074);     // Green for lower terrain  
    vec3 rock_color = vec3(0.2, 0.6, 0.2);      // Grey for higher terrain
    vec3 snow_color = vec3(0.6, 0.6, 0.6);   // White for peaks
    
    vec3 final_color;
    
    // Mix colors based on height (noise value)
    if (noise_val < 0.3) {
        final_color = mix(grass_color, rock_color, noise_val * 2.5);
    } else {
        final_color = mix(snow_color, rock_color, (noise_val - 0.4) * 1.67);
    }
    
    // Apply simple lighting
    float ambient = 0.3;
    vec3 light_dir = normalize(vec3(1, 1, 1));
    float diffuse = max(dot(normalize(frag_normal), light_dir), 0);
    
    // Combine lighting with color
    out_color = vec4(final_color * (ambient + diffuse), 1);
}