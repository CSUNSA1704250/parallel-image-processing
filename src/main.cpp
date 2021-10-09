#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "CImg.h"

using namespace cimg_library;

// Calculate the histogram of an image region
void Histogram(const CImg<unsigned char>& image, const std::pair<int, int>& x0,
               const std::pair<int, int>& x1, const int channel,
               std::vector<int>& hist) {
  for (int i = x0.first; i < x1.first; i++) {
    for (int j = x0.second; j < x1.second; j++) {
      hist[image(i, j, channel)]++;
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel) {
  std::vector<int> hist(256, 0);

  // clang-format off
  Histogram(image, {0, 0}, {image.width(), image.height()}, channel, hist);
  // clang-format on

  return hist;
}

int main(int argc, char* argv[]) {
  if (argc == 3) {
    std::map<std::string, int> colors{{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};

    // Input image
    CImg<unsigned char> image(argv[1]);
    // Histogram color intensity
    const int kColor = colors[argv[2]];

    auto start = std::chrono::steady_clock::now();
    std::vector<int> hist = ImageAnalysis(image, kColor);
    auto end = std::chrono::steady_clock::now();

    for (int x : hist) {
      std::cout << x << std::endl;
    }

    auto diff = end - start;

    std::cout << "Elapsed time in milliseconds: "
              << std::chrono::duration<double, std::milli>(diff).count()
              << std::endl;

    return EXIT_SUCCESS;
  } else {
    std::cout << "Please follow template." << std::endl;
    std::cout << "./main.out <input_image> <color>" << std::endl;

    return EXIT_FAILURE;
  }
  return 0;
}
