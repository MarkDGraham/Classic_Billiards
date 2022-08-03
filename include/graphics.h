#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include "Physics.h"
#include <vector>

class Graphics
{
public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height);
    void CameraMovement(int& cond, bool& tog, int togCount);
    void Update(unsigned int dt, float sysSpeed, bool uiChange);
    void changeAmbientLight(bool brighter);
    void ChangeSpotRadius(bool bigger);
    void ChangeSpotIntensity(bool brighter);
    void ChangeSpotSpec(bool brighter);
    void ChangePlungerPower(int blockPower);
    void Render();
    bool isFragShader = true;

    GameLogic rules;
    int round = 1, score1 = 0, score2 = 0, score3 = 0;
    int scoreTotal = 0, maxRound = 3;
    //Object pointer for instantiating new Objects
    vector<Object*> objectsVec;
    Physics *m_physics;

private:
    std::string ErrorString(GLenum error);



    Camera *m_camera;
    Shader *m_shader;
    Shader *m_shader_frag;
    vector<Shader*> m_Shaders;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    GLint m_normMatrix;
    GLint m_viewPos;

    GLint m_projectionMatrix2;
    GLint m_viewMatrix2;
    GLint m_modelMatrix2;

    GLint m_normMatrix2;
    GLint m_viewPos2;

    //Ambient uniform locations
    GLint m_globalAmbient;
    GLint m_globalAmbient2;


    //spotlight uniform locations
    GLint m_slAmb;
    GLint m_slDiff;
    GLint m_slSpec;
    GLint m_slPos;
    GLint m_slDir;
    GLint m_slCutoff;
    GLint m_slExp;

    //pointlight uniform locations
    GLint m_pAmb;
    GLint m_pSpec;
    GLint m_pDiff;
    GLint m_pPos;

    //Global Light
    glm::vec3 globalAmbient = glm::vec3(0.9f, 0.8f, 0.8f);

    //Point Light
    glm::vec3 p_amb = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 p_Spec  = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 p_Diff  = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 pPos = glm::vec3(-12, 2, -20);

    //Direction Light
    glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specular  = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 diffuse  = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

    //Spot Light
    glm::vec3 slPos = glm::vec3(0.0f, 21.0f, -10.0f);//initial position
    glm::vec3 slDir = glm::vec3(0.0f, -10.0f, 0.0f);//initial direction
    glm::vec3 slAmb = glm::vec3(0.6f, 0.2f, 0.6f);//initial ambient
    glm::vec3 slSpec = glm::vec3(1.0f, 1.0f, 1.0f);//intial specular
    glm::vec3 slDiff = glm::vec3(1.0f, 1.0f, 1.0f);
    float slCutoff = glm::cos(glm::radians(80.0f));
    float slExponent = 1.0f;
};

#endif /* GRAPHICS_H */
