#include "CImg.h"
using namespace cimg_library;

int main() {
  const CImg<float> img = CImg<float>("data/lena.jpg").histogram(256);
  img.display_graph(0, 3);
  return 0;
}
