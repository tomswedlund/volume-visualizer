#ifndef __VolumeRenderer_h__
#define __VolumeRenderer_h__

class ICamera;
class Image;
class IVolume;

class VolumeRenderer {
public:
	static void Render(const IVolume& volume, const ICamera& camera, Image& image);
};

#endif // __VolumeRenderer_h__