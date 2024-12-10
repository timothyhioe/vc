#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vec_normal;
layout(location = 2) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 project;
uniform vec3 lightPos;
uniform int objectType;

out vec3 colorVS;
out vec3 normal, lightDir, viewDir;

void main() {
    gl_Position = project * view * model * vec4(pos, 1.0);

    if (objectType == 0){
        //Robot
        vec4 n = vec4(vec_normal, 1.0);
        mat4 normalMat = transpose(inverse(view * model));
        normal = (normalMat * n).xyz;

        colorVS = color;
    } else if (objectType == 1){
        //Light
        colorVS = color;
    }

    vec4 lp = vec4(view * vec4(lightPos, 1.0));
    vec4 P = vec4(view * model * vec4(pos, 1.0));
    lightDir = (lp - P).xyz;

    viewDir = -P.xyz;
}