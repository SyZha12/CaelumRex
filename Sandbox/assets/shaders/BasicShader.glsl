#type vertex
#version 460 core

layout(location = 0) in vec3 v_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(v_Position, 1.0);
}

#type fragment
#version 460 core

layout(location = 0) out vec4 color;

void main()
{
    color = vec4(0.5, 0.2, 0.8, 1.0);
}