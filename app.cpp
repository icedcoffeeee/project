#include "app.h"

void app(GlobalState *state, ImGuiIO io) {
  static float shift_x = 0;
  ImGui::Begin("Controls");
  {
    ImGui::Text("Controls the feeds");
    ImGui::SliderFloat("Shift X", &shift_x, 0, 100);
  }
  ImGui::End();

  static ImageTexture m = ImageTexture::fromCamera(0);
  m.videoRead();
  ImGui::Begin("Camera 1");
  { ImGui::Image(m.getOpenglTexture(), m.getSize() / 2.); }
  ImGui::End();
};
