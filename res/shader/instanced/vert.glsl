#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in mat4 instanceMatrix;

out vec2 oTexCoord;

uniform mat4 view, projection;

void main() {
    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0f);
    oTexCoord = aTexCoord;
}
