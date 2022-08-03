
#include "engine.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "Physics.h"
#include <string.h>

Engine::Engine(string name, int width, int height)
{
    m_WINDOW_NAME = name;
    m_WINDOW_WIDTH = width;
    m_WINDOW_HEIGHT = height;
    m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
    m_WINDOW_NAME = name;
    m_WINDOW_HEIGHT = 0;
    m_WINDOW_WIDTH = 0;
    m_FULLSCREEN = true;
}

Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    delete m_window;
    delete m_graphics;
    m_window = NULL;
    m_graphics = NULL;
}

bool Engine::Initialize()
{
    // Start a window
    m_window = new Window();
    if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
    {
        printf("The window failed to initialize.\n");
        return false;
    }

    // Start the graphics
    m_graphics = new Graphics();
    if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
    {
        printf("The graphics failed to initialize.\n");
        return false;
    }

    // Set the time
    m_currentTimeMillis = GetCurrentTimeMillis();

    // Setup Dear ImGui binding
    ImGui::CreateContext();
    ImGuiIO& imgui_io = ImGui::GetIO(); (void)imgui_io;
    ImGui_ImplSDL2_InitForOpenGL(m_window->getSDLWindow(), m_window->getGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsDark();

    // No errors
    return true;
}

void Engine::Run()
{
    m_running = true;
    GameLogic rules;

    while(m_running)
    {
        // Update the DT
        m_DT = getDT();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_window->getSDLWindow());
        ImGui::NewFrame();

        // Check the keyboard input
        while(SDL_PollEvent(&m_event) != 0)
        {
            Keyboard();
            Mouse();
        }

        // Update and render the graphics
        m_graphics->Update(m_DT, systemSpeed, uiChange);
        m_graphics->CameraMovement(cond, tog, togCount);
        m_graphics->Render();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Physics collision;
        m_graphics->m_physics->detectCollision();

        // Swap to the Window
        m_window->Swap();
    }
}

void Engine::Keyboard()
{
    btTransform newTrans;
    //newTrans.setOrigin(btVector3(0,0,0));

    if(m_event.type == SDL_QUIT)
    {
        m_running = false;
    }
    else if (m_event.type == SDL_KEYDOWN)
    {
        // handle key down events here
        switch(m_event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                m_running = false;
                break;
             case SDLK_t:
                if(tog)
		{
		    tog = false;
		    togCount++;
		}
                else
		{
	            tog = true;
		    togCount++;
		}
                break;

            case SDLK_i:
                m_graphics->isFragShader = !m_graphics->isFragShader;
                break;

            case SDLK_LEFTBRACKET:
                m_graphics->changeAmbientLight(false);
                break;

            case SDLK_RIGHTBRACKET:
                m_graphics->changeAmbientLight(true);
                break;

            case SDLK_SEMICOLON:
                m_graphics->ChangeSpotRadius(false);
                break;

            case SDLK_QUOTE:
                m_graphics->ChangeSpotRadius(true);
                break;

            case SDLK_PERIOD:
                m_graphics->ChangeSpotIntensity(true);
                break;

            case SDLK_COMMA:
                m_graphics->ChangeSpotIntensity(false);
                break;

            case SDLK_MINUS:
                m_graphics->ChangeSpotSpec(true);
                break;
            case SDLK_EQUALS:
                m_graphics->ChangeSpotSpec(false);
                break;

            case SDLK_1:

                break;
            case SDLK_2:

                break;
            case SDLK_3:

                break;



            case SDLK_r:
	           cond = 1;m_graphics->CameraMovement(cond, tog, togCount);
	           break;
            case SDLK_w:
	           cond = 2;
	           break;
            case SDLK_s:
	           cond = 3;
	           break;
            case SDLK_a:
	           cond = 4;
	           break;
            case SDLK_d:
	           cond = 5;
	           break;
            case SDLK_q:
	           cond = 6;
	           break;
            case SDLK_e:
	            cond = 7;
	            break;

            case SDLK_SPACE:
                m_graphics->objectsVec.at(2)->readyState = false;
                m_graphics->objectsVec.at(2)->aimingState = true;
                break;

            case SDLK_LEFT:
                if(m_graphics->objectsVec.at(2)->readyState)
                    m_graphics->objectsVec.at(2)->posAngle += glm::radians(2.0f);
                break;
            case SDLK_RIGHT:
                if(m_graphics->objectsVec.at(2)->readyState)
                    m_graphics->objectsVec.at(2)->posAngle -= glm::radians(2.0f);
                break;
            case SDLK_UP:
                //m_graphics->objectsVec.at(2)->offset += glm::vec3(0,0,0.3);
                break;
            case SDLK_DOWN:
                //m_graphics->objectsVec.at(2)->offset += glm::vec3(0,0,-0.3);
                break;

            case SDLK_z:
                m_graphics->m_physics->ballReset();

                break;

            case SDLK_x:
                m_graphics->m_physics->Tilt();

                break;
            case SDLK_HOME:
                var[8] = 1.0;
                break;
             case SDLK_g:
                m_graphics->m_physics->ballReset();
	            break;
	         case SDLK_PAGEUP:
	            uiChange = true;
                break;
	         case SDLK_PAGEDOWN:
	            uiChange = false;
                break;

            default:
                break;

        }
    }

    else if (m_event.type == SDL_MOUSEWHEEL) {
        if (m_event.wheel.y > 0) // scroll up
        {
            cond = 7;
        } else if (m_event.wheel.y < 0) // scroll down
        {
            cond = 6;
        }
    }

        else if (m_event.type == SDL_KEYUP)
    {
        // handle key up events here
        switch(m_event.key.keysym.sym) {
            case SDLK_LEFT:

                break;

            case SDLK_RIGHT:

                break;

            case SDLK_SPACE:
                m_graphics->objectsVec.at(2)->aimingState = false;
                m_graphics->objectsVec.at(2)->shootingState = true;

                break;

            default:
                break;
        }
    }

}

void Engine::Mouse()
{
    if(m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch(m_event.button.button)
        {
            case SDL_BUTTON_LEFT:
                var[2] = 1;
                break;
            case SDL_BUTTON_RIGHT:
                var[2] = -1;
                break;
            case SDL_BUTTON_MIDDLE:
                var[2] = 0;
                break;
            default:
                break;
        }
    }
}

unsigned int Engine::getDT()
{
    long long TimeNowMillis = GetCurrentTimeMillis();
    assert(TimeNowMillis >= m_currentTimeMillis);
    unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
    m_currentTimeMillis = TimeNowMillis;
    return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
    timeval t;
    gettimeofday(&t, NULL);
    long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    return ret;
}
