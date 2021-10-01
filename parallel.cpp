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

std::mutex hist_i_mutex;  // Protect access to hist[i]

// Calculate the histogram of an image region
void Histogram(const CImg<unsigned char>& image, const std::pair<int, int>& x0,
               const std::pair<int, int>& x1, const int channel,
               std::vector<int>& hist) {
  for (int i = x0.first; i < x1.first; i++) {
    for (int j = x0.second; j < x1.second; j++) {
      hist_i_mutex.lock();
      hist[image(i, j, channel)]++;
      hist_i_mutex.unlock();
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel, const int num_threads) {
  const int kIntensity = 256;
  std::vector<int> hist(kIntensity, 0);
  std::vector<std::pair<int, int>> regions_coords = Regions(image, num_threads);

  // spawn threads
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(
        Histogram, std::ref(image), std::ref(regions_coords[2 * i]),
        std::ref(regions_coords[2 * i + 1]), channel, std::ref(hist)));
  }

  // sync threads
  for (auto& t : threads) {
    t.join();
  }

  return hist;
}

// Returns pixel intensity on given channel, full speed ahead!
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel) {
  const int num_threads = std::thread::hardware_concurrency();
  return ImageAnalysis(image, channel, num_threads);
}

int main() {
  CImg<unsigned char> image("examples/data/lena.jpg");

  /*
  const int kColor = 0;
  const int kThreads = 4;
  std::vector<int> hist = ImageAnalysis(image, kColor, kThreads);
  */
  const int kColor = 0;
  std::vector<int> hist = ImageAnalysis(image, kColor);

  for (int x : hist) {
    std::cout << x << std::endl;
  }

  return 0;
}
