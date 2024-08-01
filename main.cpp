#include "app.h"

// Main code
int main(int, char **) {
  // Create application window
  // ImGui_ImplWin32_EnableDpiAwareness();
  WNDCLASSEXW wc = {sizeof(wc), CS_OWNDC,   WndProc,
                    0L,         0L,         GetModuleHandle(nullptr),
                    nullptr,    nullptr,    nullptr,
                    nullptr,    L"Project", nullptr};
  ::RegisterClassExW(&wc);

  static const float aspect = 16.0 / 9.0;
  static const float height = 800;
  static const float width = aspect * height;
  HWND hwnd =
      ::CreateWindowW(wc.lpszClassName, L"Project", WS_OVERLAPPEDWINDOW, 10, 10,
                      width, height, nullptr, nullptr, wc.hInstance, nullptr);

  // Initialize OpenGL
  if (!CreateDeviceWGL(hwnd, &g_MainWindow)) {
    CleanupDeviceWGL(hwnd, &g_MainWindow);
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 1;
  }
  wglMakeCurrent(g_MainWindow.hDC, g_hRC);

  // Show the window
  ::ShowWindow(hwnd, SW_SHOWDEFAULT);
  ::UpdateWindow(hwnd);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  ImGui::SetNextWindowSize(io.DisplaySize);

  // Setup Dear ImGui style
  ImGui::StyleColorsLight();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplWin32_InitForOpenGL(hwnd);
  ImGui_ImplOpenGL3_Init();

  // Load Fonts
  io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\CascadiaMono.ttf", 14.0f);

  // Our state
  GlobalState state{};

  // Main loop
  bool done = false;
  while (!done) {
    // Poll and handle messages (inputs, window resize, etc.)
    // See the WndProc() function below for our to dispatch events to the Win32
    // backend.
    MSG msg;
    while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
      if (msg.message == WM_QUIT)
        goto exit;
    }
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    app(&state, io);

    // Rendering
    ImGui::Render();
    glViewport(0, 0, g_Width, g_Height);
    glClearColor(state.clear_color.x, state.clear_color.y, state.clear_color.z,
                 state.clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Present
    ::SwapBuffers(g_MainWindow.hDC);
  }
exit:

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  CleanupDeviceWGL(hwnd, &g_MainWindow);
  wglDeleteContext(g_hRC);
  ::DestroyWindow(hwnd);
  ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

  return 0;
}

// Helper functions
bool CreateDeviceWGL(HWND hWnd, WGL_WindowData *data) {
  HDC hDc = ::GetDC(hWnd);
  PIXELFORMATDESCRIPTOR pfd = {0};
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;

  const int pf = ::ChoosePixelFormat(hDc, &pfd);
  if (pf == 0)
    return false;
  if (::SetPixelFormat(hDc, pf, &pfd) == FALSE)
    return false;
  ::ReleaseDC(hWnd, hDc);

  data->hDC = ::GetDC(hWnd);
  if (!g_hRC)
    g_hRC = wglCreateContext(data->hDC);
  return true;
}

void CleanupDeviceWGL(HWND hWnd, WGL_WindowData *data) {
  wglMakeCurrent(nullptr, nullptr);
  ::ReleaseDC(hWnd, data->hDC);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd,
                                                             UINT msg,
                                                             WPARAM wParam,
                                                             LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if
// dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your
// main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to
// your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from
// your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg) {
  case WM_SIZE:
    if (wParam != SIZE_MINIMIZED) {
      g_Width = LOWORD(lParam);
      g_Height = HIWORD(lParam);
    }
    return 0;
  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
      return 0;
    break;
  case WM_DESTROY:
    ::PostQuitMessage(0);
    return 0;
  }
  return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}
