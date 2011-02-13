
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/eval.hpp"
#include "viennamath/substitute.hpp"
#include "viennamath/diff.hpp"

#include "viennamath/equation.hpp"



int main()
{
  viennamath::variable<0> x;
  viennamath::variable<1> y;
  viennamath::variable<2> z;
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);
  viennamath::ct_constant<8> c8;
  viennamath::expr<> x_pow_4 = (x*x)*(x*x);
  viennamath::expr<> test(2.0);

  //compile time:
  std::cout << viennamath::make_equation(x*x + y, x + y) << std::endl;
  std::cout << viennamath::make_equation(x*x + y, x) << std::endl;
  std::cout << viennamath::make_equation(x*x + y, c8) << std::endl;

  std::cout << viennamath::make_equation(x, x + y) << std::endl;
  std::cout << viennamath::make_equation(x, y) << std::endl;
  std::cout << viennamath::make_equation(x, c8) << std::endl;

  std::cout << viennamath::make_equation(c8, x + y) << std::endl;
  std::cout << viennamath::make_equation(c8, x) << std::endl;
  std::cout << viennamath::make_equation(c8, c8) << std::endl;
  
  //run time:
  std::cout << viennamath::make_equation(x, 3.0) << std::endl;
  std::cout << viennamath::make_equation(viennamath::exp(x), 3.0) << std::endl;
  //std::cout << viennamath::make_equation(5.0, 3.0) << std::endl; //is not allowed
  std::cout << viennamath::make_equation(c4, 3.0) << std::endl; //this is mathematical nonsense! How to handle?
  std::cout << viennamath::make_equation(x*x + y, 3.0) << std::endl;
  std::cout << viennamath::make_equation(x_pow_4 + y*y, 5.0) << std::endl;
  std::cout << viennamath::make_equation(x_pow_4 + y*y, x*x + y) << std::endl;
   

  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}