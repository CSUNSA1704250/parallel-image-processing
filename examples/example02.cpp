#include "CImg.h"
using namespace cimg_library;

int main() {
  const CImg<float> img = CImg<float>("data/lena.jpg").histogram(256);
  img.display_graph("My histogram", 2);
  return 0;
}
