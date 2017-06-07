#include <SDL2\SDL.h>
#include "SDLGLApp.h"
#include "SDLGLWindow.h"
#include "IAppContext.h"

SDLGLApp::SDLGLApp() {
}

SDLGLApp::~SDLGLApp() {
	for each (std::pair<unsigned int, SDLGLWindow*> pair in _windows) {
		delete pair.second;
	}
}

bool SDLGLApp::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	return true;
}

void SDLGLApp::run() {
	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event) != 0) {
			if (_windows.find(event.window.windowID) == _windows.end()) {
				continue;
			}
			SDLGLWindow* window = _windows[event.window.windowID];
			SDL_GL_MakeCurrent(window->window(), window->glContext());

			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYUP:
				window->context()->onKeyPress(event.key.keysym.sym, false);
				break;

			case SDL_KEYDOWN:
				window->context()->onKeyPress(event.key.keysym.sym, true);
				break;

			case SDL_MOUSEBUTTONUP:
				window->context()->onMouseButtonPress(event.button.button, false);
				break;

			case SDL_MOUSEBUTTONDOWN:
				window->context()->onMouseButtonPress(event.button.button, true);
				break;

			case SDL_MOUSEMOTION:
				window->context()->onMouseMove(event.motion.xrel, event.motion.yrel);
				break;

			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					window->context()->onWindowResize(event.window.data1, event.window.data2);
					break;
				case SDL_WINDOWEVENT_CLOSE:
					delete _windows[event.window.windowID];
					_windows.erase(event.window.windowID);
					if (_windows.size() == 0) {
						running = false;
					}
					break;
				}
				break;
			}
		}

		for each (std::pair<unsigned int, SDLGLWindow*> pair in _windows) {
			SDL_GL_MakeCurrent(pair.second->window(), pair.second->glContext());
			pair.second->context()->render();
			SDL_GL_SwapWindow(pair.second->window());
		}
	}
}

void SDLGLApp::createWindow(IAppContext* ctx) {
	SDLGLWindow* w = new SDLGLWindow(this, ctx);
	if (w->init()) {
		Uint32 winId = SDL_GetWindowID(w->window());
		_windows.insert_or_assign(winId, w);
		ctx->window(w);
	}
}