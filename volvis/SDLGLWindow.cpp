#include "IAppContext.h"
#include "SDLGLApp.h"
#include "SDLGLWindow.h"

SDLGLWindow::SDLGLWindow(SDLGLApp* app, IAppContext* ctx)
	: _ctx(ctx), _app(app), _window(nullptr) {
}

SDLGLWindow::~SDLGLWindow() {
	if (_window != nullptr) {
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
	if (_ctx != nullptr) {
		_ctx->cleanup();
		delete _ctx;
	}
	SDL_GL_DeleteContext(_glCtx);
}

SDL_Window* SDLGLWindow::window() {
	return _window;
}

SDL_GLContext SDLGLWindow::glContext() {
	return _glCtx;
}

SDLGLApp* SDLGLWindow::app() {
	return _app;
}

IAppContext* SDLGLWindow::context() {
	return _ctx;
}

bool SDLGLWindow::init() {
	_window = SDL_CreateWindow("Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500, 500,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (_window == nullptr) {
		return false;
	}
	
	_glCtx = SDL_GL_CreateContext(_window);
	_ctx->init();
	return true;
}