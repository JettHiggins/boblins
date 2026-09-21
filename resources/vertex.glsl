#version 330 core

in vec3 vertexPosition;
in mat4 instanceTransform;
in vec2 vertexTexCoord;

uniform mat4 mvp;
uniform mat4 matNormal;

out vec2 fragTexCoord;

void main(){
  fragTexCoord = vertexTexCoord;

  gl_Position = mvp * instanceTransform * vec4(vertexPosition, 1.0);
}
