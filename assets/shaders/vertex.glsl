#version 330 core

layout (location = 0) in vec3 pos;      // vertices position in local space
layout (location = 1) in vec3 normal;   // Normals
layout (location = 2) in vec3 colorRGB; // Màu sắc (r, g, b)

out vec3 fragNormal; //Position des Fragments im Weltkoordinatensystem
out vec3 fragPos;    // Normalenvektor im Weltkoordinatensystem
out vec3 colorVS;   // Farbe für das Fragment

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragNormal = mat3(model) * normal;        // Umwandeln vector *normal von local space zu worldpsace
    fragPos = vec3(model * vec4(pos, 1.0));  // berechnen koordinanten im world space, view space, immer Z sehen
    colorVS = colorRGB;
    gl_Position = projection * view * vec4(fragPos, 1.0); // verbinden Model, View và Projection Matrix (NDC)
}
