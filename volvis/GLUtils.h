#ifndef __GLUtils_h__
#define __GLUtils_h__

#include "Vector3.h"

class GLUtils {
public:
	static void setPerspectiveProjection(float fov, int width, int height);
	static void setOthoProjection(int width, int height);
};

#endif // __GLUtils_h__