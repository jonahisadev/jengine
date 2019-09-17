

linux: test.cpp
	g++ test.cpp -o test -L ../cmake-build-debug -ljengine -lglfw3 -pthread -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl -lSOIL

mac: test.cpp
	g++ test.cpp -o test -std=c++14 -L ../cmake-build-debug -ljengine `pkg-config glfw3 --cflags --libs` -framework OpenGL

clean:
	rm test
