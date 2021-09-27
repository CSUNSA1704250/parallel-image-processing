#include <iostream>
#include <vector>

#include "CImg.h"

using namespace cimg_library;

std::vector<int> histogram(const CImg<unsigned char>& image, int channel) {
  std::vector<int> res(256, 0);
  for (int i = 0; i < image.width(); i += 1) {
    for (int j = 0; j < image.height(); j += 1) {
      res[image(i, j, channel)]++;
    }
  }
  return res;
}

int main() {
  CImg<unsigned char> image("examples/data/lena.jpg");

  CImgDisplay main_disp(image, "Lena <3");

  std::vector<int> res = histogram(image, 0);

  for (int x : res) {
    std::cout << x << std::endl;
  }

  return 0;
}
