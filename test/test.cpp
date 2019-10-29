#include "../JEngine.h"
#include "../Graphics/Display.h"

int main()
{
	using namespace JEngine;

	Display window(800, 600, "OpenGL 3", false);
	window.vsync(true);
	window.center();

	Quad mesh(100, 100, 100, 100);
	mesh.setColor(0, 255, 128);

	auto render = [&](Matrix4f screen) {
		window.clear(0, 128, 128);

		mesh.render(screen);
	};

	auto update = [&](float delta) {
		if (window.key('D'))
			mesh.translate(20 * delta, 0);
		if (window.key('A'))
			mesh.translate(-20 * delta, 0);
		if (window.key('S'))
			mesh.translate(0, 20 * delta);
		if (window.key('W'))
			mesh.translate(0, -20 * delta);

		mesh.rotate(45);
	};

	window.run(render, update);
	return 0;
}