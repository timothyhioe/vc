#version 330

in vec3 colorVS;
in vec3 normal, lightDir, viewDir;

uniform vec3 lightColor;
uniform vec3 matSpecular;
uniform float matShininess;
uniform int objectType;

out vec4 color;

void main() {
    if (objectType == 0){
        //Robot
        vec3 N = normalize(normal);
        vec3 L = normalize(lightDir);

        float cosa = max(0.0, dot(N,L));
        vec3 diffuseTerm = colorVS * lightColor;
        color = vec4(diffuseTerm * cosa, 1.0);

        //ambient ocmponent
        float ambientStrength = 0.2;
        vec3 ambientColor = colorVS; // this could also be a global ambient color
        vec3 ambientTerm = ambientColor * lightColor * ambientStrength;
        color += vec4(ambientTerm, 1.0);

        vec3 V = normalize(viewDir);
        vec3 R = normalize(reflect(-L,N));
        float cosBeta = max(0.0, dot(R,V));
        float cosBetak = pow(cosBeta, matShininess);
        vec3 specularTerm = matSpecular * lightColor;
        color += vec4(specularTerm * cosBetak, 1.0);
    } else if (objectType == 1){
        color = vec4(lightColor.x, lightColor.y, lightColor.z, 1.0);
    }
}