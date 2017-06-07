#include "VolumeRenderer.h"
#include "Color.h"
#include "ICamera.h"
#include "Integrator.h"
#include "Image.h"
#include "IVolume.h"
#include "Utils.h"

void VolumeRenderer::Render(const IVolume& volume, const ICamera& camera, Image& image) {
	BoundingBox bbox(volume.width(), volume.height(), volume.depth());
	Integrator integrator(&bbox, &volume);
	for (int row = 0; row < image.height(); ++row) {
		for (int col = 0; col < image.width(); ++col) {
			float x, y;
			Utils::transformImageCoords(image.width(), image.height(), col, row, x, y);
			Ray ray(camera.generateRay(x, y));
			float value = integrator.integrate(ray);
			Color color(value, value, value);
			image.set(col, image.height() - row, color);
		}
	}
}