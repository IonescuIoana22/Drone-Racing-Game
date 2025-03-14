#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction, light_direction1;
uniform vec3 light_position, light_position1;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;
uniform int isSpotlight;
uniform float cut_off_angle;

// Output
layout(location = 0) out vec4 out_color;


void main()
{


    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25f;
    float diffuse_light = 0;
    float specular_light = 0;

    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    vec3 R = reflect(-L, N);

    ambient_light = material_kd * 0.5f;
    diffuse_light = material_kd * max(dot(N, L), 0);

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(V, R), 0), material_shininess);
    }

    float ambient_light1 = 0.25f;
    float diffuse_light1 = 0;
    float specular_light1 = 0;

    //vec3 N1 = normalize(world_normal);
    vec3 L1 = normalize(light_position1 - world_position);
    vec3 V1 = normalize(eye_position - world_position);
    vec3 H1 = normalize(L1 + V1);
    vec3 R1 = reflect(-L1, N);

    ambient_light1 = material_kd * 0.5f;
    diffuse_light1 = material_kd * max(dot(N, L1), 0);

    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light1 > 0)
    {
        specular_light1 = material_ks * pow(max(dot(V1, R1), 0), material_shininess);
    }

    vec3 color_light = vec3(0.f);

    if (isSpotlight == 1) {
    
        float cut_off = radians(cut_off_angle);
        float spot_light = dot(-L, light_direction);
        float spot_light_limit = cos(cut_off);

        if (spot_light > spot_light_limit)
        {
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = linear_att * linear_att;
            color_light = object_color * (ambient_light + light_att_factor * (diffuse_light + specular_light));
        } else {
        color_light = object_color * ambient_light;
        }
    } else {
        float d = distance(light_position, world_position);
        float attenuation = 1.0 / (1 + d * d);

        float d1 = distance(light_position1, world_position);
        float attenuation1 = 1.0 / (1 + d1 * d1);

        color_light = object_color * (ambient_light + (attenuation * (diffuse_light + specular_light)) + (attenuation1 * (diffuse_light1 + specular_light1)));
    }

    // TODO(student): Write pixel out color
    out_color = vec4(color_light, 1.f);

}
