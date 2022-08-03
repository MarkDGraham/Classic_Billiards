#version 330

in vec4 varyingLight;
in vec2 TextCoords;

out vec4 frag_color; 

uniform sampler2D sampler;

void main(void)
{
  frag_color = texture2D(sampler, TextCoords) * varyingLight;
}
