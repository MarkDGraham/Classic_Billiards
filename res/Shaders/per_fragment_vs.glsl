#version 330

layout (location = 0) in vec3 v_position; 
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_textCoord; 
layout (location = 3) in vec3 v_normal;

out vec3 FragPos;
out vec3 Normal;
out vec2 TextCoords;

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct DirLight
{
  vec3 direction;	
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
};

struct SpotLight
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  vec3 position;
  vec3 direction;
  float cutoff;
  float exponent;

  //float constant;
  //float linear;
  //float quadratic;
};


uniform vec3 globalAmbient;
uniform SpotLight spotLight;
uniform PointLight pointLight;
uniform Material material;
//uniform mat4 norm_matrix;
uniform vec3 viewPos;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;

void main(void)
{
  mat4 norm_matrix = mat4(transpose(inverse(modelMatrix)));
  Normal = normalize((norm_matrix * vec4(v_normal, 1.0)).xyz);;
  FragPos = vec3(modelMatrix * vec4(v_position, 1.0));
  gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(v_position, 1.0);
  TextCoords = v_textCoord;
}
