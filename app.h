#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS

#include "image_texture.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

#include <opencv2/opencv.hpp>
#include <windows.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <GL/GL.h>
#include <tchar.h>

struct WGL_WindowData {
  HDC hDC;
};

static HGLRC g_hRC;
static WGL_WindowData g_MainWindow;
static int g_Width;
static int g_Height;

// Forward declarations of helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data);
void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data);
void ResetDeviceWGL();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct GlobalState {
  ImVec4 clear_color = ImVec4(0., 0., 0., 0.);
};

void app(GlobalState *state, ImGuiIO io);
