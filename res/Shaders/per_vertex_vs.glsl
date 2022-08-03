#version 330

layout (location = 0) in vec3 v_position; 
layout (location = 1) in vec3 v_color;
layout (location = 2) in vec2 v_textCoord; 
layout (location = 3) in vec3 v_normal;

out vec4 varyingLight;
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
uniform Material material;
uniform mat4 norm_matrix;
uniform vec3 viewPos;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;


vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main(void)
{
  vec3 viewDir = normalize(viewPos - v_position);
  
  vec4 P = (projectionMatrix * viewMatrix * modelMatrix) * vec4(v_position, 1.0);
  mat4 norm_matrix = mat4(transpose(inverse(modelMatrix)));
  vec3 N = normalize((norm_matrix * vec4(v_normal, 1.0)).xyz);
  vec3 FragPos = vec3(modelMatrix * vec4(v_position, 1.0));
  //vec3 L = normalize(light.position = P.xyz);
  //vec3 V = normalize(-P.xyz);
  //vec3 R = reflect(-L,N);

  vec3 spot = CalcSpotLight(spotLight, N, FragPos, viewDir);
  vec3 result = globalAmbient + spot;
  result += CalcSpotLight(spotLight, N, FragPos, viewDir);
  vec4 v = vec4(v_position, 1.0);
  varyingLight = vec4(result.xyz, 1.0);
  gl_Position = P;
  TextCoords = v_textCoord;
}

/*
// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}
*/


// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 25.0);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + 0.35 * distance + 0.44 * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient ;
    vec3 diffuse = light.diffuse * diff ;
    vec3 specular = light.specular * spec ;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}


// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 45.0);
    // attenuation
    //float distance = length(light.position - fragPos);
    //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    if(theta > light.cutoff) 
    {
      float epsilon = light.exponent - light.cutoff;
      float intensity = clamp((theta - light.cutoff) / epsilon, 0.0, 1.0);
      // combine results
      vec3 ambient = light.ambient;
      vec3 diffuse = light.diffuse * diff;
      vec3 specular = light.specular * spec;
      ambient *= intensity;
      diffuse *= intensity;
      specular *= intensity;
    return (ambient + diffuse + specular);
    }
    else 
    {
      return vec3(0.0, 0.0, 0.0);
    }
}
