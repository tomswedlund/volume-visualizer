#ifndef __SDLGLApp_h__
#define __SDLGLApp_h__

#include <map>

class IAppContext;
class SDLGLWindow;

class SDLGLApp {
public:
	SDLGLApp();
	~SDLGLApp();

	bool init();
	void run();
	void createWindow(IAppContext* ctx);

private:
	std::map<unsigned int, SDLGLWindow*> _windows;
};

#endif // __SDLGLApp_h__
