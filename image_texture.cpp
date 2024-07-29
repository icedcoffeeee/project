#include "image_texture.h"

void ImageTexture::DelImageTexture() {
  glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
  glDeleteTextures(1, &my_opengl_texture);
}

ImageTexture ImageTexture::fromFile(std::string filename) {
  ImageTexture m;

  cv::Mat frame = cv::imread(filename);

  m.setImage(frame);

  return m;
}

ImageTexture ImageTexture::fromCamera(int camera) {
  ImageTexture m;
  m.vc = cv::VideoCapture(camera);

  return m;
}

void ImageTexture::videoRead() {
  vc.read(video_frame);
  setImage(video_frame);
}

void ImageTexture::setImage(cv::Mat pframe) {
  cv::cvtColor(pframe, pframe, cv::COLOR_BGR2RGB);

  width = pframe.cols;
  height = pframe.rows;

  glGenTextures(1, &my_opengl_texture);
  glBindTexture(GL_TEXTURE_2D, my_opengl_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, pframe.data);
}

void *ImageTexture::getOpenglTexture() {
  return (void *)(intptr_t)my_opengl_texture;
};

ImVec2 ImageTexture::getSize() { return ImVec2(width, height); };
