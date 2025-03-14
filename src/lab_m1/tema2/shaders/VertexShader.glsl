#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec3 frag_position;
out vec3 frag_normal;
out vec3 frag_color;
out float noise_val;

// Noise function from The Book of Shaders
float rand(vec2 n) { 
    return fract(sin(dot(n, vec2(12.9898, 4.1414))) * 43758.5453);
}

float noise(vec2 p){
    vec2 ip = floor(p);
    vec2 u = fract(p);
    u = u*u*(3.0-2.0*u);
    
    float res = mix(
        mix(rand(ip),rand(ip+vec2(1.0,0.0)),u.x),
        mix(rand(ip+vec2(0.0,1.0)),rand(ip+vec2(1.0,1.0)),u.x),u.y);
    return res*2.0-1.0;
}

void main()
{
    // Apply noise to vertex height
    vec2 position_xz = v_position.xz;
    float frequency = 0.05; // Adjust this value to change terrain frequency
    float amplitude = 20; // Adjust this value to change terrain height
    
    // Generate noise value
    float n = noise(position_xz * frequency);
    noise_val = (n + 1.0) * 0.5; // Normalize to [0,1]
    
    // Modify vertex position
    vec3 modified_position = v_position;
    modified_position.y += noise_val * amplitude;
    
    // Compute gl_Position
    frag_position = modified_position;
    frag_normal = v_normal;
    frag_color = v_color;
    gl_Position = Projection * View * Model * vec4(modified_position, 1.0);
}