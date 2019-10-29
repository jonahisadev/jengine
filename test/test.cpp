#include "../JEngine.h"
#include "../Graphics/Display.h"

int main()
{
	using namespace JEngine;

	Display window(800, 600, "OpenGL 3", false);
	// window.vsync(true);
	// window.center();

	// Quad mesh(-0.5f, -0.5f, 1.0f, 1.0f);

	float pos[] = {
	    200, 200,
		200, 100,
		100, 100,
		100, 200
	};
	
	float color[] = {0};
	
	int els[] = {
	    0, 1, 3,
	    1, 2, 3
	};

	Mesh mesh(pos, color, els, 4, 6);

	auto render = [&]() {
		window.clear(0, 128, 128);

		mesh.render();
	};

	auto update = [&](float delta) {

	};

	window.run(render, update);
	return 0;
}