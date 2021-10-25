#include <chrono>
#include <iostream>
#include <vectorclass.h>

extern "C" {

  Vec8i kernel(Vec8f ax, Vec8f ay) {
    // future results, all to -1 initially
    Vec8i res{-1};
    // remember which pixels are already diverging
    Vec8fb cmp{false};

    // ---------  part you have to work on
    Vec8f x = 0;
    Vec8f y = 0;
    for (int n = 1; n <= 100; n++) {
      auto newx = x*x - y*y + ax;
      auto newy = 2*x*y + ay;
      // -------- part you have to work on
      
      // comparison now gives a vector of booleans
      Vec8fb newcmp = (4 < newx*newx + newy*newy);
      // if any is true
      if (horizontal_or(newcmp)) {
        // we fill res for the pixels reaching divergence on this round
        res = select(andnot(newcmp, cmp), Vec8i{n}, res);
        // and update our map of all pixels already diverging
        cmp = cmp | newcmp;
      }
      // no need to continue if all pixels are over
      if (horizontal_and(newcmp)) {
        break;
      }
      x = newx;
      y = newy;
    }
    return res;
  }
  
  void mandel(int* buffer,
              const float minx,
              const float dx,
              const unsigned int nx,
              const float miny,
              const float dy,
              const unsigned int ny) {
    auto start = std::chrono::steady_clock::now();
    Vec8f ay{miny}; // vector of 8 x miny value
    // loop one pixel at a time in y
    for (unsigned int any = 0; any < ny; ay += dy, any++) {
      // vector of first 8 pixels in x
      Vec8f ax{minx, minx+dx, minx+2*dx, minx+3*dx, minx+4*dx, minx+5*dx, minx+6*dx, minx+7*dx};
      // loop 8 by 8 pixels in x
      for (unsigned int anx = 0; anx < nx; ax += 8*dx, anx += 8) {
        // compute and store back 8 pixels in one go
        kernel(ax, ay).store(buffer+any*nx+anx);
      }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in microseconds : " 
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " us" << std::endl;
  }
}
