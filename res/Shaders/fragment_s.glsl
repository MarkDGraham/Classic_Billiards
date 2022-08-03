#version 330
        
smooth in vec3 color; 

in vec2 TextCoords;
          
out vec4 frag_color; 

uniform sampler2D sampler;

void main(void) 
{ 
	frag_color = texture2D(sampler, TextCoords); 
}
