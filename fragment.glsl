uniform vec3 viewPos = vec3(0.0, 0.0, 0.0);    // Camera
uniform vec3 emissiveColor;                    // farbe von cube

out vec4 color;

void main() {

    vec3 norm = normalize(fragNormal);           // normalize vector Normal
    vec3 lightDir = normalize(lightPos - fragPos); // Die Richtung von pixel zu Lichtquelle
    vec3 viewDir = normalize(viewPos - fragPos);  // Die Richtung von pixel zu Kamera

    // Ambient Lighting
    vec3 ambient = 0.2 * lightColor;
    //diffuser Term
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor; //dot(norm,lightdir) schneiden negativ werte ab,  => Defuse Beleutung berechnung: lichintensitaet similator

    //Phong Shading
    // specular lighting, reflect: Berechnet den Reflexionsvektor des Lichts (Lichtquelle , Normalenverktor)
    vec3 specular = pow(max(dot(viewDir, reflect(-lightDir, norm)), 0.0), 8.0) * lightColor;//dot vektor => Kosinus winkel, und schneiden werte ab
    //der stellt sicher  die Reflexion íntensiver
    vec3 emissive = emissiveColor;

    // alle teil verbinden
    vec3 result = (ambient + diffuse + specular + emissive) * colorVS;
    color = vec4(result, 1.0); // Alpha = 1.0
}

