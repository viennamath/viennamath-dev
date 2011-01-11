
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "viennamath/vector.hpp"
#include "viennamath/unknown.hpp"
#include "viennamath/constant.hpp"
#include "viennamath/expression.hpp"

template <typename E, typename T, typename U>
void operations_test(E & e, T const & t, U const & u)
{
  e = t + u;
  e = u + t;
  /*e = t - u;
  e = u - t;
  e = t * u;
  e = u * t;
  e = t / u;
  e = u / t;*/
}


int main()
{
  viennamath::unknown<double, 0> x;
  viennamath::unknown<double, 1> y;
  viennamath::unknown<double, 2> z;
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);
  viennamath::constant<long, viennamath::compile_time_constant<8> > c8;
  viennamath::op_plus plus;
  viennamath::expr e1 = x + y;
  viennamath::expr e2 = c4 + c8;
  viennamath::expr e3 = e1 + e2;
  viennamath::expr e;
  
  std::vector<double> p(2);
  p[0] = 1;
  p[1] = 2;
  p[2] = 3;

  //compilation checks:
  operations_test(e, x, y);  
  
  std::cout << "--- Involved types ---" << std::endl;
  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
  std::cout << "z: " << z << std::endl;
  std::cout << "c4: " << c4 << std::endl;
  std::cout << "c6: " << c6 << std::endl;
  std::cout << "c8: " << c8 << std::endl;
  std::cout << "e1: " << e1 << std::endl;
  std::cout << "e2: " << e2 << std::endl;
  std::cout << "e3: " << e3 << std::endl;
  std::cout << "e: " << e << std::endl;

  std::cout << "--- Involved types ---" << std::endl;
  
  return EXIT_SUCCESS;
}