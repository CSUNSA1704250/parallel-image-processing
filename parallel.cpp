#include <iostream>
#include <thread>
#include <vector>

#include "CImg.h"

using namespace cimg_library;

// Calculate the histogram of an image region
void Histogram(const CImg<unsigned char>& image, const int x0, const int y0,
               const int x1, const int y1, const int channel,
               std::vector<int>& res) {
  for (int i = x0; i < x1; i++) {
    for (int j = y0; j < y1; j++) {
      res[image(i, j, channel)]++;
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel) {
  std::vector<int> res(256, 0);

  const int width = image.width();
  const int height = image.height();

  // clang-format off
  std::thread t1(Histogram, std::ref(image),
                 0, 0, width / 4, height,
                 channel, std::ref(res));
  std::thread t2(Histogram, std::ref(image),
                 width / 4, 0, (width / 4) * 2, height,
                 channel, std::ref(res));
  std::thread t3(Histogram, std::ref(image),
                 (width / 4) * 2, 0, (width / 4) * 3, height,
                 channel, std::ref(res));
  std::thread t4(Histogram, std::ref(image),
                 (width / 4) * 3, 0, width, height,
                 channel, std::ref(res));
  // clang-format on

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  return res;
}

int main() {
  CImg<unsigned char> image("examples/data/lena.jpg");

  std::vector<int> res = ImageAnalysis(image, 0);

  for (int x : res) {
    std::cout << x << std::endl;
  }

  return 0;
}
