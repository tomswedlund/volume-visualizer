#ifndef __IAppContext_h__
#define __IAppContext_h__

class SDLGLWindow;

class IAppContext{
public:
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void onKeyPress(int key, bool down) = 0;
	virtual void onMouseMove(int deltaX, int deltaY) = 0;
	virtual void onMouseButtonPress(char button, bool down) = 0;
	virtual void onWindowResize(int width, int height) = 0;
	virtual void cleanup() = 0;
	
	virtual void window(SDLGLWindow* w) = 0;
	virtual SDLGLWindow* window() = 0;
};

#endif // __IAppContext_h__