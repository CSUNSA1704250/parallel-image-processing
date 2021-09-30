#include <iostream>
#include <thread>
#include <vector>

#include "CImg.h"

using namespace cimg_library;

// Returns image regions coordinates according to number of threads
std::vector<std::pair<int, int>> Regions(const CImg<unsigned char>& image,
                                         const int num_threads) {
  std::vector<std::pair<int, int>> regions;
  const int r_width = image.width() / num_threads;
  const int r_height = image.height();

  for (int i = 0; i < num_threads; i++) {
    regions.push_back({i * r_width, 0});
    regions.push_back({r_width * (i + 1), r_height});
  }

  return regions;
}

// Calculate the histogram of an image region
void Histogram(const CImg<unsigned char>& image, const std::pair<int, int>& x0,
               const std::pair<int, int>& x1, const int channel,
               std::vector<int>& res) {
  for (int i = x0.first; i < x1.first; i++) {
    for (int j = x0.second; j < x1.second; j++) {
      res[image(i, j, channel)]++;
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel, const int num_threads) {
  const int kIntensity = 256;
  std::vector<int> res(kIntensity, 0);
  std::vector<std::pair<int, int>> regions_coords = Regions(image, num_threads);

  // spawn threads
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(
        Histogram, std::ref(image), std::ref(regions_coords[2 * i]),
        std::ref(regions_coords[2 * i + 1]), channel, std::ref(res)));
    for (auto x : res) {
      std::cout << x << std::endl;
    }
  }

  // sync threads
  for (auto& t : threads) {
    t.join();
  }

  return res;
}

int main() {
  CImg<unsigned char> image("examples/data/lena.jpg");

  const int kColor = 0;
  const int kThreads = 4;
  std::vector<int> res = ImageAnalysis(image, kColor, kThreads);

  for (int x : res) {
    std::cout << x << std::endl;
  }

  return 0;
}
