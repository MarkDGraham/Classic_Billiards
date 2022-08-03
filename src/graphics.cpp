#include "graphics.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

GameLogic rules;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(int width, int height)
{
    // Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
        std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
        return false;
    }
#endif

    // For OpenGL 3
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Init Camera
    m_camera = new Camera();
    if(!m_camera->Initialize(width, height))
    {
        printf("Camera Failed to Initialize\n");
        return false;
    }

    btTriangleMesh *mTableMesh = new btTriangleMesh();
    Table *pTable = new Table("../res/Models/PoolTable.obj", mTableMesh);
    btCollisionShape *tableShape = new btBvhTriangleMeshShape(mTableMesh, true);


    int test = mTableMesh->getNumTriangles();

    m_physics = new Physics();
    m_physics->PoolSetup(tableShape);

    //Objectvec order 0 table, 1 cueball, 2 cuestick, 3-17 balls 1-15

    // Create objects and push onto object vec
    pTable->mRigidBody = m_physics->tableRB;
    objectsVec.push_back(pTable);

    Sphere *cueBall = new Sphere("../res/Models/CueBall.obj", m_physics->RBVec.at(0));
    objectsVec.push_back(cueBall);

    CueStick *cueStick = new CueStick("../res/Models/PoolStick.obj", m_physics->cueStickRB);
    cueStick->mParentRB = cueBall->GetRigidBody();
    objectsVec.push_back(cueStick);


    Sphere *oneBall = new Sphere("../res/Models/OneBall.obj", m_physics->RBVec.at(1));
    objectsVec.push_back(oneBall);

    Sphere *twoBall = new Sphere("../res/Models/TwoBall.obj", m_physics->RBVec.at(2));
    objectsVec.push_back(twoBall);

    Sphere *threeBall = new Sphere("../res/Models/ThreeBall.obj", m_physics->RBVec.at(3));
    objectsVec.push_back(threeBall);

    Sphere *fourBall = new Sphere("../res/Models/FourBall.obj", m_physics->RBVec.at(4));
    objectsVec.push_back(fourBall);

    Sphere *fiveBall = new Sphere("../res/Models/FiveBall.obj", m_physics->RBVec.at(5));
    objectsVec.push_back(fiveBall);

    Sphere *sixBall = new Sphere("../res/Models/SixBall.obj", m_physics->RBVec.at(6));
    objectsVec.push_back(sixBall);

    Sphere *sevenBall = new Sphere("../res/Models/SevenBall.obj", m_physics->RBVec.at(7));
    objectsVec.push_back(sevenBall);

    Sphere *eightBall = new Sphere("../res/Models/EightBall.obj", m_physics->RBVec.at(8));
    objectsVec.push_back(eightBall);

    Sphere *nineBall = new Sphere("../res/Models/NineBall.obj", m_physics->RBVec.at(9));
    objectsVec.push_back(nineBall);

    Sphere *tenBall = new Sphere("../res/Models/TenBall.obj", m_physics->RBVec.at(10));
    objectsVec.push_back(tenBall);

    Sphere *elevenBall = new Sphere("../res/Models/ElevenBall.obj", m_physics->RBVec.at(11));
    objectsVec.push_back(elevenBall);

    Sphere *twelveBall = new Sphere("../res/Models/TwelveBall.obj", m_physics->RBVec.at(12));
    objectsVec.push_back(twelveBall);

    Sphere *thirteenBall = new Sphere("../res/Models/ThirteenBall.obj", m_physics->RBVec.at(13));
    objectsVec.push_back(thirteenBall);

    Sphere *fourteenBall = new Sphere("../res/Models/FourteenBall.obj", m_physics->RBVec.at(14));
    objectsVec.push_back(fourteenBall);

    Sphere *fifteenBall = new Sphere("../res/Models/FifteenBall.obj", m_physics->RBVec.at(15));
    objectsVec.push_back(fifteenBall);




    // Set up the shaders
    m_shader = new Shader();
    m_shader_frag = new Shader();
    if(!m_shader->Initialize())
    {
        printf("Shader Failed to Initialize\n");
        return false;
    }
    if(!m_shader_frag->Initialize())
    {
        printf("Shader_frag Failed to Initialize\n");
        return false;
    }

    // Add the vertex shader
    if(!m_shader->AddShader(GL_VERTEX_SHADER, false))
    {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }

    // Add the fragment shader
    if(!m_shader->AddShader(GL_FRAGMENT_SHADER, false))
    {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }

    // Add the vertex shader
    if(!m_shader_frag->AddShader(GL_VERTEX_SHADER, true))
    {
        printf("Vertex Shader failed to Initialize\n");
        return false;
    }

    // Add the fragment shader
    if(!m_shader_frag->AddShader(GL_FRAGMENT_SHADER, true))
    {
        printf("Fragment Shader failed to Initialize\n");
        return false;
    }

    // Connect the program
    if(!m_shader->Finalize())
    {
        printf("Program to Finalize\n");
        return false;
    }

    // Connect the program
    if(!m_shader_frag->Finalize())
    {
        printf("Program to Finalize\n");
        return false;
    }

    m_Shaders.push_back(m_shader);
    m_Shaders.push_back(m_shader_frag);

        for(int i = 0; i < 2; i++) {
        //m_Shaders.at(i)->Enable();

        if(i == 0) {
            // Locate the global ambient  in the shader
            m_globalAmbient = m_Shaders.at(i)->GetUniformLocation("globalAmbient");
            if (m_globalAmbient == INVALID_UNIFORM_LOCATION) {
                printf("m_globalAmbient not found\n");
                return false;
            }

            // Locate the spotlight fields in the shader
            m_slAmb = m_Shaders.at(i)->GetUniformLocation("spotLight.ambient");
            m_slDiff = m_Shaders.at(i)->GetUniformLocation("spotLight.diffuse");
            m_slSpec = m_Shaders.at(i)->GetUniformLocation("spotLight.specular");
            m_slPos = m_Shaders.at(i)->GetUniformLocation("spotLight.position");
            m_slDir = m_Shaders.at(i)->GetUniformLocation("spotLight.direction");
            m_slCutoff = m_Shaders.at(i)->GetUniformLocation("spotLight.cutoff");
            m_slExp = m_Shaders.at(i)->GetUniformLocation("spotLight.exponent");

	    //Locate pointlight fields in shader
            m_pAmb = m_Shaders.at(i)->GetUniformLocation("pointLight.ambient");
            m_pSpec = m_Shaders.at(i)->GetUniformLocation("pointLight.diffuse");
            m_pDiff = m_Shaders.at(i)->GetUniformLocation("pointLight.specular");
            m_pPos = m_Shaders.at(i)->GetUniformLocation("pointLight.position");

            //Locate the normal matrix
            m_normMatrix = m_Shaders.at(i)->GetUniformLocation("norm_matrix");

            //Locate the view Pos
            m_viewPos = m_shader->GetUniformLocation("viewPos");

            // Locate the projection matrix in the shader
            m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
            if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) {
                printf("m_projectionMatrix not found\n");
                return false;
            }

            // Locate the view matrix in the shader
            m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
            if (m_viewMatrix == INVALID_UNIFORM_LOCATION) {
                printf("m_viewMatrix not found\n");
                return false;
            }

            // Locate the model matrix in the shader
            m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
            if (m_modelMatrix == INVALID_UNIFORM_LOCATION) {
                printf("m_modelMatrix not found\n");
                return false;
            }

            //enable depth testing
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }
        else {
            // Locate the global ambient  in the shader
            m_globalAmbient2 = m_Shaders.at(i)->GetUniformLocation("globalAmbient");
            if (m_globalAmbient2 == INVALID_UNIFORM_LOCATION) {
                printf("m_globalAmbient not found\n");
                return false;
            }

            // Locate the spotlight fields in the shader
            m_slAmb = m_Shaders.at(i)->GetUniformLocation("spotLight.ambient");
            m_slDiff = m_Shaders.at(i)->GetUniformLocation("spotLight.diffuse");
            m_slSpec = m_Shaders.at(i)->GetUniformLocation("spotLight.specular");
            m_slPos = m_Shaders.at(i)->GetUniformLocation("spotLight.position");
            m_slDir = m_Shaders.at(i)->GetUniformLocation("spotLight.direction");
            m_slCutoff = m_Shaders.at(i)->GetUniformLocation("spotLight.cutoff");
            m_slExp = m_Shaders.at(i)->GetUniformLocation("spotLight.exponent");

	    //Locate pointlight fields in shader
            m_pAmb = m_Shaders.at(i)->GetUniformLocation("pointLight.ambient");
            m_pSpec = m_Shaders.at(i)->GetUniformLocation("pointLight.diffuse");
            m_pDiff = m_Shaders.at(i)->GetUniformLocation("pointLight.specular");
            m_pPos = m_Shaders.at(i)->GetUniformLocation("pointLight.position");


            //Locate the normal matrix
            m_normMatrix2 = m_Shaders.at(i)->GetUniformLocation("norm_matrix");

            //Locate the view Pos
            m_viewPos2 = m_Shaders.at(i)->GetUniformLocation("viewPos");

            // Locate the projection matrix in the shader
            m_projectionMatrix2 = m_Shaders.at(i)->GetUniformLocation("projectionMatrix");
            if (m_projectionMatrix2 == INVALID_UNIFORM_LOCATION) {
                printf("m_projectionMatrix not found\n");
                return false;
            }

            // Locate the view matrix in the shader
            m_viewMatrix2 = m_Shaders.at(i)->GetUniformLocation("viewMatrix");
            if (m_viewMatrix2 == INVALID_UNIFORM_LOCATION) {
                printf("m_viewMatrix not found\n");
                return false;
            }

            // Locate the model matrix in the shader
            m_modelMatrix2 = m_Shaders.at(i)->GetUniformLocation("modelMatrix");
            if (m_modelMatrix2 == INVALID_UNIFORM_LOCATION) {
                printf("m_modelMatrix not found\n");
                return false;
            }

            //enable depth testing
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
        }
    }
    return true;
}

void Graphics::Update(unsigned int dt, float sysSpeed, bool uiChange)
{
    //step physics world
    m_physics->dynamicsWorld->stepSimulation(dt, 10);

    m_physics->checkGameStatus();
    //m_physics->anyBallsMoving();
    //m_physics->EightBallInPocket();
    //m_physics->updateActiveBalls();

    // Update the Objects
    for(int i = 0; i < objectsVec.size(); i++) {
        objectsVec.at(i)->Update(dt, sysSpeed);
    }

    if(uiChange)
    {
         //Main Menu
        {
            ImGui::Begin("Pool Controls");
            ImGui::Separator();
            ImGui::Separator();

            //Lighting Controls
            ImGui::Text("Lighting Controls:");
            ImGui::Text("  i -- Switch between Vertex and Fragment Shaders");
            ImGui::Text("  [ -- Increase Brightness");
            ImGui::Text("  ] -- Decrease Brightness");

            ImGui::Separator();
            ImGui::Separator();

            //General Camera Controls
            ImGui::Text("Camera Controls:");
            ImGui::Text("  r -- Reset Camera to Default Position");
            ImGui::Text("  t -- Toggle between Pan and Rotate Camera");

            //Spacer
            ImGui::Text("  ");

            //Camera Controls
            ImGui::Text("  (Pan) Camera Controls:");
            ImGui::Text("    w -- Pan Camera Up");
            ImGui::Text("    s -- Pan Camera Down");
            ImGui::Text("    a -- Pan Camera Left");
            ImGui::Text("    d -- Pan Camera Right");
            ImGui::Text("    e -- Move Camera Forward");
            ImGui::Text("    q -- Move Camera Backwards");

            //Spacer
            ImGui::Text("  ");

            //Toggled Camera Controls
            ImGui::Text("  (Rotate) Camera Controls:");
            ImGui::Text("    w -- Pitch Camera Backward");
            ImGui::Text("    s -- Pitch Camera Forward");
            ImGui::Text("    a -- Yaw Camera Left");
            ImGui::Text("    d -- Yaw Camera Right");

            ImGui::Separator();
            ImGui::Separator();

            //Paddle Movement Controls
            ImGui::Text("Cue Controls:");
            ImGui::Text("  Left Arrow -- Cue Rotate Left");
            ImGui::Text("  Right Arrow -- Cue Rotate Right");
            ImGui::Text("  SPACE -- Launch ball");
            //ImGui::Text("  g -- Reset Cue Ball");

            ImGui::End();
        }
    }
    else
    {
{
            ImGui::Begin("Current Game Stats:");

            ImGui::Text("  Player 1: Solids (Balls 1 - 7)");
            ImGui::Text("  Player 2: Stripes (Balls 9 - 15)");

            // Spacer
            ImGui::Separator();
            ImGui::Separator();

            // Current Ball Count
            ImGui::Text("Player 1 balls remaining:");
            std::string player1Balls = " ";
            for(int i = 0; i < 8; i++)
            {
                if(i != 0 && i < 8 && m_physics->activeBalls[i+1] == true)
                {
                    player1Balls += ", ";
                }

                if(m_physics->activeBalls[i + 1] == true)
                {
                    player1Balls += std::to_string(i + 1);
                }
            }

            ImGui::Text(player1Balls.c_str());
            ImGui::Text("Player 2 balls remaining:");
            std::string player2Balls = " ";
            for(int i = 7; i < 15; i++)
            {
                if(i != 7 && i < 15 && m_physics->activeBalls[i+1] == true)
                {
                    player2Balls += ", ";
                }

                if(m_physics->activeBalls[i + 1] == true)
                {
                    player2Balls += std::to_string(i+1);
                }
            }
            ImGui::Text(player2Balls.c_str());

            // Spacer
            ImGui::Separator();
            ImGui::Separator();

            ImGui::Text("Player's Turn:");
            if(m_physics->player == 1 && m_physics->winner == 1)
            {
                ImGui::Text("Player 1 is the winner!");
            }
            else if(m_physics->player == 1 && m_physics->winner == 0)
            {
                ImGui::Text("Player 1");
            }
            else if(m_physics->player == 2 && m_physics->winner == 2)
            {
                ImGui::Text("Player 2 is the winner!");
            }
            else
            {
                ImGui::Text("Player 2");
            }
            ImGui::End();
        }
    }



    m_physics->detectCollision();
}


void Graphics::CameraMovement(int& cond, bool& tog, int togCount)
{
	m_camera->Movement(cond, tog, togCount);
}

void Graphics::Render()
{
    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(!isFragShader) {
        // Start the correct program
        m_shader->Enable();

        //Set viewPos
        glUniform3fv(m_viewPos, 1, glm::value_ptr(m_camera->GetPos()));

        //Set global Ambient uniform
        glUniform3fv(m_globalAmbient, 1, glm::value_ptr(globalAmbient));

        glm::vec3 tempPos = glm::vec3(objectsVec.at(0)->GetModel()[3][0], objectsVec.at(0)->GetModel()[3][1],
                                      objectsVec.at(0)->GetModel()[3][2]);
        tempPos.y += 10.0f;
        //tempPos.z += 15.0f;

        //set Spotlight uniforms
        glUniform3fv(m_slAmb, 1, glm::value_ptr(slAmb));
        glUniform3fv(m_slDiff, 1, glm::value_ptr(slDiff));
        glUniform3fv(m_slSpec, 1, glm::value_ptr(slSpec));
        glUniform3fv(m_slPos, 1, glm::value_ptr(tempPos));
        glUniform3fv(m_slDir, 1, glm::value_ptr(slDir));
        glUniform1f(m_slCutoff, slCutoff);
        glUniform1f(m_slExp, slExponent);

	//set Pointlight uniforms
        glUniform3fv(m_pAmb, 1, glm::value_ptr(p_amb));
        glUniform3fv(m_pSpec, 1, glm::value_ptr(p_Spec));
        glUniform3fv(m_pDiff, 1, glm::value_ptr(p_Diff));
        glUniform3fv(m_pPos, 1, glm::value_ptr(pPos));

        // Send in the projection and view to the shader
        glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
        glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


        // Render the object
        for (int i = 0; i < objectsVec.size(); i++) {
            glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(objectsVec.at(i)->GetModel()));
            objectsVec.at(i)->Render();
        }
    }
    else {
        // Start the correct program
        m_shader_frag->Enable();

        //Set viewPos
        glUniform3fv(m_viewPos2, 1, glm::value_ptr(m_camera->GetPos()));

        //Set global Ambient uniform
        glUniform3fv(m_globalAmbient2, 1, glm::value_ptr(globalAmbient));

        glm::vec3 tempPos = glm::vec3(objectsVec.at(0)->GetModel()[3][0], objectsVec.at(0)->GetModel()[3][1],
                                      objectsVec.at(0)->GetModel()[3][2]);
        tempPos.y += 10.0f;
        //tempPos.z += 15.0f;

        //set Spotlight uniforms
        glUniform3fv(m_slAmb, 1, glm::value_ptr(slAmb));
        glUniform3fv(m_slDiff, 1, glm::value_ptr(slDiff));
        glUniform3fv(m_slSpec, 1, glm::value_ptr(slSpec));
        glUniform3fv(m_slPos, 1, glm::value_ptr(tempPos));
        glUniform3fv(m_slDir, 1, glm::value_ptr(slDir));
        glUniform1f(m_slCutoff, slCutoff);
        glUniform1f(m_slExp, slExponent);

	//set Pointlight uniforms
        glUniform3fv(m_pAmb, 1, glm::value_ptr(p_amb));
        glUniform3fv(m_pSpec, 1, glm::value_ptr(p_Spec));
        glUniform3fv(m_pDiff, 1, glm::value_ptr(p_Diff));
        glUniform3fv(m_pPos, 1, glm::value_ptr(pPos));

        // Send in the projection and view to the shader
        glUniformMatrix4fv(m_projectionMatrix2, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
        glUniformMatrix4fv(m_viewMatrix2, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));


        // Render the object
        for (int i = 0; i < objectsVec.size(); i++) {
            glUniformMatrix4fv(m_modelMatrix2, 1, GL_FALSE, glm::value_ptr(objectsVec.at(i)->GetModel()));
            objectsVec.at(i)->Render();
        }
    }


    // Get any errors from OpenGL
    auto error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        string val = ErrorString( error );
        std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
    }
}

std::string Graphics::ErrorString(GLenum error)
{
    if(error == GL_INVALID_ENUM)
    {
        return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
    }

    else if(error == GL_INVALID_VALUE)
    {
        return "GL_INVALID_VALUE: A numeric argument is out of range.";
    }

    else if(error == GL_INVALID_OPERATION)
    {
        return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
    }

    else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
    {
        return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
    }

    else if(error == GL_OUT_OF_MEMORY)
    {
        return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
    }
    else
    {
        return "None";
    }
}

void Graphics::changeAmbientLight(bool brighter) {
    if(brighter) {
        globalAmbient += 0.05;
    }
    else {
        globalAmbient -= 0.05;
    }
}

void Graphics::ChangeSpotRadius(bool bigger) {
    if(bigger) {
        slCutoff -= 0.01;
    }
    else {
        slCutoff += 0.01;
    }
}

void Graphics::ChangeSpotIntensity(bool brighter) {
    if(brighter) {
        slExponent -= 0.01;
    }
    if(!brighter) {
        slExponent += 0.01;
    }
}

void Graphics::ChangeSpotSpec(bool brighter) {
    if(brighter) {
        slSpec -= 0.1;
    }
    if(!brighter) {
        slSpec += 0.1;
    }

}

void Graphics::ChangePlungerPower(int blockPower) {

    switch(blockPower) {
        case 1:
            objectsVec.at(0)->power = 0.10;
            break;
        case 2:
            objectsVec.at(0)->power = 0.12;
            break;
        case 3:
            objectsVec.at(0)->power = 0.16;
            break;
        default:
            break;

    }
}
