.PHONY : all, rebuild, clean
all : build/yasc
rebuild : clean all
clean :
	-rm -R build/*
# main target
build/yasc : build/display.o build/mesh.o build/yasc.o build/utils.o build/main.o | build/
	g++ -o build/yasc  build/display.o build/mesh.o build/yasc.o build/utils.o build/main.o -lSDL2 -lGL -lGLEW
# object targets
build/display.o : src/display.cpp src/display.h src/utils.h | build/
	g++ -o build/display.o -c src/display.cpp -Wno-write-strings
build/mesh.o : src/mesh.cpp src/mesh.h src/display.h | build/
	g++ -o build/mesh.o -c src/mesh.cpp -Wno-write-strings
build/yasc.o : src/yasc.cpp src/yasc.h src/display.h src/utils.h | build/
	g++ -o build/yasc.o -c src/yasc.cpp -Wno-write-strings
build/utils.o : src/utils.cpp src/utils.h | build/
	g++ -o build/utils.o -c src/utils.cpp -Wno-write-strings
build/main.o : src/main.cpp src/yasc.h src/display.h | build/
	g++ -o build/main.o -c src/main.cpp -Wno-write-strings
# object dir targets
build/ :
	mkdir -p build
