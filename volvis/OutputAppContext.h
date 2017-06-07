#ifndef __OutputAppContext_h__
#define __OutputAppContext_h__

class Image;
class SDLGLWindow;

#include "IAppContext.h"

class OutputAppContext : public IAppContext {
public:
	OutputAppContext(Image* image);

	virtual void init();
	virtual void render();
	virtual void onKeyPress(int key, bool down);
	virtual void onMouseMove(int deltaX, int deltaY);
	virtual void onMouseButtonPress(char button, bool down);
	virtual void onWindowResize(int width, int height);
	virtual void cleanup();

	virtual void window(SDLGLWindow* w);
	virtual SDLGLWindow* window();

private:
	Image* _image;
	SDLGLWindow* _window;
	unsigned int _textureId;
};

#endif // __OutputAppContext_h__