#version 330 core

out vec4 FragColor;

in vec3 oColor;
in vec2 oTexCoord;

uniform sampler2D ourTexture;
uniform float time;

void main() {
    vec4 color = texture(ourTexture, oTexCoord);
    if (color.a < 0.1) {
        discard;
    } 
    FragColor = color;
}
