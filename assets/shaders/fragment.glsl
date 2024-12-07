#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 color;

out vec4 FragColor;

void main() {

    //color = vec4(colorVS.x, colorVS.y, colorVS.z, 1.0);
    FragColor = vec4(color, 1.0); // RGB + alpha (1.0 for opaque)
}