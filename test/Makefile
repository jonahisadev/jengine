

linux: test.cpp
	g++ test.cpp -o test -L ../cmake-build-debug -ljengine -lglfw3 -pthread -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lSOIL -lfreetype -I/usr/local/include/freetype2 -lopenal -lglm -g

mac: test.cpp
	g++ test.cpp -o test -std=c++14 -L ../cmake-build-debug -ljengine `pkg-config glfw3 --cflags --libs` -framework OpenGL -lSOIL -lfreetype -I/usr/local/include/freetype2 -lopenal -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

clean:
	rm test
