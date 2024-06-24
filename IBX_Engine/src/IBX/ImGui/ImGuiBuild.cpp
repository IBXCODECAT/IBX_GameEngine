#include "ibxpch.h"

// Suppress warnings in imgui_impl_opengl3.cpp (We assume that code outside our domain is safe)
// #define _CRT_SECURE_NO_WARNINGS

// Define IMGUI_IMPL_OPENGL_LOADER_GLAD before including imgui_impl_opengl3.cpp to use glad
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <backends/imgui_impl_opengl3.cpp>
#include <backends/imgui_impl_glfw.cpp>