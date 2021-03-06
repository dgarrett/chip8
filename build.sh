#!/usr/bin/env bash

# c++ --std=c++17 `sdl2-config --cflags` -I lib/imgui -I lib/imgui/backends src/*.cpp lib/imgui/backends/imgui_impl_sdl.cpp lib/imgui/backends/imgui_impl_opengl3.cpp lib/imgui/imgui*.cpp `sdl2-config --libs` -framework OpenGl -framework CoreFoundation

cmake -G "Unix Makefiles" -B build
make -C build