#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::Movement(int& cond, bool& tog, int togCount)
{
    if(cond == 1) //r key
    {
        tempEyePos = eyePos;
        tempFocusPos = focusPo;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        maxKeyX = 0;
        maxKeyY = 0;
	maxKeyZ = 0;
    }

    if(cond == 2) // w key
    {
        if(!tog)
        {
            tempEyePos.z += 0.5f;
        }
        tempFocusPos.z += 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        if(tog % 2)
	{
	  maxKeyY = 0;
        }
        maxKeyY++;
    }
    
    if(cond == 3) // s key
    {
        if(!tog)
        {
            tempEyePos.z -= 0.5f;
        }
        tempFocusPos.z -= 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        if(tog % 2)
	{
	  maxKeyY = 0;
        }
        maxKeyY--;
    }

    if(cond == 4) // a key
    {
        if(!tog)
        {
            tempEyePos.x += 0.5f;
        }
        tempFocusPos.x += 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        if(tog % 2)
	{
	  maxKeyX = 0;
        }
	maxKeyX++;
    }

    if(cond == 5) // d key
    {
        if(!tog)
        {
            tempEyePos.x -= 0.5f;
        }
        tempFocusPos.x -= 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        if(tog % 2)
	{
	  maxKeyX = 0;
        }
        maxKeyX--;
    }
    
    if(cond == 6) // q key
    {
        //tempEyePos.z -= 0.5f;
        tempEyePos.y += 0.5f;
        //tempFocusPos.z -= 0.5f;
        tempFocusPos.y += 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        //maxKeyZ++;
        maxKeyY++;
    }
    
    if(cond == 7) // e key
    {
        //tempEyePos.z += 0.5f;
        tempEyePos.y -= 0.5f;
	//tempFocusPos.z += 0.5f;
        tempFocusPos.y -= 0.5f;
        view = glm::lookAt(tempEyePos, tempFocusPos, positiveY);
        cond = 0;
        //maxKeyZ--;
        maxKeyY--;
    }

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine
  view = glm::lookAt(  eyePos, //Eye Position
                      focusPo, //Focus point
                      positiveY); //Positive Y is up

  tempFocusPos = focusPo;
  tempEyePos = eyePos;
  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 1000.0f); //Distance to the far plane,
  return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}


