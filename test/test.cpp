#include "../JEngine.h"
#include "../Graphics/Display.h"
#include "../Graphics/TexturedQuad.h"
#include "../Graphics/Font.h"

int main()
{
	using namespace JEngine;

	Display window(800, 600, "OpenGL 3", false);
	window.vsync(true);
	window.center();

	Font font("Roboto-Regular.ttf", 24, &window);
	TexturedQuad tex(200, 200, 128, 128, "coyote.png");

	auto render = [&](Matrix4f screen) {
		window.clear(0, 128, 128);

		tex.render(screen);

		std::string fps = "FPS: " + std::to_string(window.getFPS());
		font.render(10, 10 + font.height(fps), fps, {1, 1, 1});
	};

	auto update = [&](float delta) {
		tex.rotate(15 * delta);
	};

	window.run(render, update);
	return 0;
}