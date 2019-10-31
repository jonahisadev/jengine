#include "../JEngine.h"
#include "../Graphics/Display.h"

int main()
{
	using namespace JEngine;

	Display window(800, 600, "OpenGL 3", false);
	window.vsync(true);
	window.center();

	float buffer[] = {
		100, 100, 0, 0,
		200, 100, 1, 0,
		200, 200, 1, 1,
		100, 200, 0, 1
	};

	int els[] = {
		0, 1, 2,
		0, 3, 2
	};

	TexturedQuad tex(100, 100, 100, 100, "coyote.png");
	// TexturedMesh mesh(buffer, {1, 1, 1}, els, 4, 6, "gradient.png");
	// Mesh mesh(buffer, {1, 1, 1}, els, 4, 6);
	// Quad mesh(100, 100, 100, 100);

	auto render = [&](Matrix4f screen) {
		window.clear(0, 128, 128);

		// mesh.render(screen);
		tex.render(screen);
	};

	auto update = [&](float delta) {
		tex.rotate(15 * delta);

		if (window.mousePressed(Mouse::MouseLeft))
			tex.setCenter(window.mousePosition());
	};

	window.run(render, update);
	return 0;
}