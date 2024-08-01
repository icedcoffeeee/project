#include "app.h"

void app(GlobalState *state, ImGuiIO io) {
  ImVec2 disp = io.DisplaySize;

  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(disp.x / 2, disp.y));
  ImGui::Begin("Controls", 0, ImGuiWindowFlags_NoCollapse);
  ImGui::Text("Hello World");
  ImGui::End();

  static ImageTexture m0 = ImageTexture::fromCamera(0);
  m0.videoRead();

  ImGui::SetNextWindowPos(ImVec2(disp.x / 2, 0));
  ImGui::SetNextWindowSize(ImVec2(disp.x / 2, disp.y / 2));
  ImGui::Begin("Camera 1", 0, ImGuiWindowFlags_NoTitleBar);
  ImGui::Image(m0.getOpenglTexture(), ImVec2(disp.x / 2, disp.y / 2));
  ImGui::End();

  ImGui::SetNextWindowPos(ImVec2(disp.x / 2, disp.y / 2));
  ImGui::SetNextWindowSize(ImVec2(disp.x / 2, disp.y / 2));
  ImGui::Begin("Camera 2", 0, ImGuiWindowFlags_NoTitleBar);
  ImGui::Image(m0.getOpenglTexture(), ImVec2(disp.x / 2, disp.y / 2));
  ImGui::End();

  return;
};
