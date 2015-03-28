precision mediump float;

uniform sampler2D texture;

varying vec2 texCoordVar;
varying vec4 texShadeColor;

void main()
{
  gl_FragColor = texShadeColor * texture2D( texture, texCoordVar);
}