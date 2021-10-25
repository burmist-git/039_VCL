#include <chrono>
#include <iostream>

int kernel(float ax, float ay);

extern "C" {
  
  void mandel(int* buffer,
              const float minx,
              const float dx,
              const unsigned int nx,
              const float miny,
              const float dy,
              const unsigned int ny) {
    auto start = std::chrono::steady_clock::now();
    float ay = miny;
    for (unsigned int any = 0; any < ny; ay += dy, any++) {
      float ax = minx;
      for (unsigned int anx = 0; anx < nx; ax += dx, anx++) {
        buffer[any*nx+anx] = kernel(ax, ay);
      }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in microseconds : " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " us" << std::endl;
  }

}

int kernel(float ax, float ay) {
  float x = 0;
  float y = 0;
  for (int n = 1; n <= 100; n++) {
    auto newx = x*x - y*y + ax;
    auto newy = 2*x*y + ay;
    if (4 < newx*newx + newy*newy) {
      return n;
    }
    x = newx;
    y = newy;
  }
  return -1;
}
