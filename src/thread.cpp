#include <iostream>
#include <map>
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
               std::vector<int>& hist) {
  for (int i = x0.first; i < x1.first; i++) {
    for (int j = x0.second; j < x1.second; j++) {
      hist[image(i, j, channel)]++;
    }
  }
}

// Returns pixel intensity on given channel
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel, const int num_threads) {
  const int kIntensity = 256;
  std::vector<int> hist(kIntensity, 0);
  std::vector<std::vector<int>> results(num_threads,
                                        std::vector<int>(kIntensity, 0));
  std::vector<std::pair<int, int>> regions_coords = Regions(image, num_threads);

  // spawn threads
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; i++) {
    threads.push_back(std::thread(
        Histogram, std::ref(image), std::ref(regions_coords[2 * i]),
        std::ref(regions_coords[2 * i + 1]), channel, std::ref(results[i])));
  }

  // sync threads
  for (auto& t : threads) {
    t.join();
  }

  // sum region histograms
  for (int i = 0; i < kIntensity; i++) {
    for (auto& h : results) {
      hist[i] += h[i];
    }
  }

  return hist;
}

// Returns pixel intensity on given channel, full speed ahead!
std::vector<int> ImageAnalysis(const CImg<unsigned char>& image,
                               const int channel) {
  const int num_threads = std::thread::hardware_concurrency();
  return ImageAnalysis(image, channel, num_threads);
}

int main(int argc, char* argv[]) {
  if (argc == 4) {
    std::map<std::string, int> colors{{"RED", 0}, {"GREEN", 1}, {"BLUE", 2}};

    // Input image
    CImg<unsigned char> image(argv[1]);
    // Histogram color intensity
    const int kColor = colors[argv[2]];
    // Number of threads
    const int kThreads = std::atoi(argv[3]);

    auto start = std::chrono::steady_clock::now();
    std::vector<int> hist = ImageAnalysis(image, kColor, kThreads);
    auto end = std::chrono::steady_clock::now();

    auto diff = end - start;

    // print num_threads and elapsed time in milliseconds
    std::cout << kThreads << ","
              << std::chrono::duration<double, std::milli>(diff).count()
              << std::endl;

    return EXIT_SUCCESS;
  } else {
    std::cout << "Please follow template." << std::endl;
    std::cout << "./thread.out <input_image> <color> <num_threads>"
              << std::endl;

    return EXIT_FAILURE;
  }
}
