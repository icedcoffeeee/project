#pragma once

// copied from
// https://github.com/ashitani/opencv_imgui_viewer/blob/master/cv2viewer.cpp

#include "imgui.h"
#include <opencv2/opencv.hpp>
#include <windows.h>

#include <GL/GL.h>

class ImageTexture {
private:
  int width, height;
  GLuint my_opengl_texture;
  cv::VideoCapture vc;
  cv::Mat video_frame;

public:
  void DelImageTexture();                             // destructor
  static ImageTexture fromFile(std::string filename); // from file
  static ImageTexture fromCamera(int camera);         // from camera
  void videoRead();
  void setImage(cv::Mat frame); // from cv::Mat (BGR)
  void *getOpenglTexture();
  ImVec2 getSize();
};
