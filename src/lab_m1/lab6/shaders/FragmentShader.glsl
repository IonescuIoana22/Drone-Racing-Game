#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 frag_position;
in vec3 frag_color;
in vec2 frag_texcoord;
in vec3 frag_normal;

// Output
layout(location = 0) out vec3 out_color;
layout(location = 1) out vec3 out_normal;
layout(location = 2) out vec2 out_texcoord;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec3(frag_normal);
    out_normal = vec3(frag_normal);
    out_texcoord = vec2(frag_texcoord);
}
