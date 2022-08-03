#version 330

in vec3 FragPos;
in vec3 Normal;
in vec2 TextCoords;

out vec4 FragColor;

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
uniform mat4 norm_matrix;
uniform vec3 viewPos;

uniform mat4 projectionMatrix; 
uniform mat4 viewMatrix; 
uniform mat4 modelMatrix;

uniform sampler2D sampler;

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
//vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main(void)
{
  vec3 result = vec3(texture2D(sampler, TextCoords)) * globalAmbient;
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  result += CalcSpotLight(spotLight, Normal, FragPos, viewDir);
  result += CalcPointLight(pointLight, Normal, FragPos, viewDir);
  FragColor = vec4(result, 1.0);
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
    vec3 ambient = light.ambient * vec3(texture2D(sampler, TextCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(sampler, TextCoords));
    vec3 specular = light.specular * spec * vec3(texture2D(sampler, TextCoords));
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
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 25.0);
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
      vec3 ambient = light.ambient * vec3(texture2D(sampler, TextCoords));
      vec3 diffuse = light.diffuse * diff * vec3(texture2D(sampler, TextCoords));
      vec3 specular = light.specular * spec * vec3(texture2D(sampler, TextCoords));
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
