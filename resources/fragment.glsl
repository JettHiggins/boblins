#version 330 core

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 FragColor;

void main(){
  vec4 fColor = texture(texture0, fragTexCoord);

  FragColor = fColor * colDiffuse;
}
