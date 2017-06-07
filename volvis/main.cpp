#include <iostream>
#include "SDLGLApp.h"
#include "SDLGLWindow.h"
#include "TestAppContext.h"
#include "OutputAppContext.h"
#include "Image.h"

int main(int argc, char **argv) {
	//Image* image = new Image("output.png");
	IAppContext* ctx = new TestAppContext();
	SDLGLApp app;
	if (app.init()) {
		app.createWindow(ctx);
		app.run();
	}
	return 0;
}