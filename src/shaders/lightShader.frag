#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform vec3 lightColor;

void main(){
    FragColor = vec4(lightColor, 1.0) * texture(texture_diffuse1, texCoords);
}
