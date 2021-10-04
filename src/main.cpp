#include <iostream>
#include <vector>

#include "CImg.h"

using namespace cimg_library;

// Calculate the histogram of an image region
void Histogram(const CImg<unsigned char>& image, const int x0, const int y0,
               const int x1, const int y1, const int channel,
               std::vector<int>& hist) {
  for (int i = x0; i < x1; i++) {
    for (int j = y0; j < y1; j++) {
      hist[image(i, j, channel)]++;
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel) {
  std::vector<int> hist(256, 0);

  const int width = image.width();
  const int height = image.height();

  // clang-format off
  Histogram(image, 0, 0, width / 4, height,
            channel, hist);
  Histogram(image, (width / 4), 0, (width / 4) * 2, height,
            channel, hist);
  Histogram(image, (width / 4) * 2, 0, (width / 4) * 3, height,
            channel, hist);
  Histogram(image, (width / 4) * 3, 0, width, height,
            channel, hist);
  // clang-format on

  return hist;
}

int main() {
  CImg<unsigned char> image("examples/data/lena.jpg");

  std::vector<int> hist = ImageAnalysis(image, 0);

  for (int x : hist) {
    std::cout << x << std::endl;
  }

  return 0;
}