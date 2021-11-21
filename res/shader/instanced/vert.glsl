#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 i_InstanceTexCoord;
layout (location = 2) in mat4 i_InstanceMatrix;

out vec2 oTexCoord;

uniform mat4 view, projection;

void main() {
    gl_Position = projection * view * i_InstanceMatrix * vec4(aPos, 1.0f);
    oTexCoord = i_InstanceTexCoord;
}
