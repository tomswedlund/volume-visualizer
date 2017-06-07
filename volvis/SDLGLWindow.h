#ifndef __SDLApp_h__
#define __SDLApp_h__

#include <SDL2/SDL.h>

class IAppContext;
class SDLGLApp;

class SDLGLWindow {
public:
	SDLGLWindow(SDLGLApp* app, IAppContext* ctx);
	~SDLGLWindow();

	SDL_Window* window();
	SDL_GLContext glContext();
	SDLGLApp* app();
	IAppContext* context();
	bool init();

private:
	IAppContext* _ctx;
	SDLGLApp* _app;
	SDL_Window* _window;
	SDL_GLContext _glCtx;
};

#endif // __SDLApp_h__