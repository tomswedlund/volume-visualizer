#include <iostream>
#include "SDLGLApp.h"
#include "SDLGLWindow.h"
#include "TestAppContext.h"

int main(int argc, char **argv) {
	IAppContext* ctx = new TestAppContext();
	SDLGLApp app;
	if (app.init()) {
		app.createWindow(ctx);
		app.run();
	}
	return 0;
}