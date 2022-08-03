#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    void Movement(int& cond, bool& tog, int togCount);
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    glm::vec3  GetPos() {return tempEyePos;};
  
  private:
    glm::mat4 projection;
    glm::mat4 view;
    int maxKeyX = 0, maxKeyY = 0, maxKeyZ = 0;
    glm::vec3 eyePos = glm::vec3(0.0, 80.0, 0.0);
    glm::vec3 focusPo = glm::vec3(0.0, 0.0, 0.01);
    glm::vec3 positiveY = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 tempEyePos = glm::vec3(0.0, 80.0, 0.0);
    glm::vec3 tempFocusPos;
};

#endif /* CAMERA_H */
