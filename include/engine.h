#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"
#include "imgui.h"

class Engine
{
public:
    Engine(string name, int width, int height);
    Engine(string name);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    void Mouse();
    unsigned int getDT();
    int orbSpeed = 1;
    long long GetCurrentTimeMillis();

    int cond, togCount;
    bool tog;
    GameLogic rules;
    Physics phys;
    //Float passed to graphics update to change the speed of the entire system
    float systemSpeed = 0.4f;

    float var[10] = {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0};


private:
    // Window related variables
    Window *m_window;
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
    bool uiChange = true;
};

#endif // ENGINE_H
