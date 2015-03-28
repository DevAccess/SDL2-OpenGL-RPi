// Position, color, and texture shader

attribute vec3 LVertexPos;
attribute vec4 LVertexColor;
attribute vec2 LTexCoord;

uniform mat4 projectionMatrix;  
uniform mat4 viewMatrix;  
uniform mat4 modelMatrix;

varying vec2 texCoordVar;
varying vec4 texShadeColor;

void main()
{
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(LVertexPos, 1.0);
  texCoordVar = LTexCoord;
  texShadeColor = LVertexColor;
}