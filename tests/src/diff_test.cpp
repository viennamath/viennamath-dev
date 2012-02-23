
/* =======================================================================
   Copyright (c) 2012, Institute for Microelectronics,
                       Institute for Analysis and Scientific Computing,
                       TU Wien.
                             -----------------
               ViennaMath - Symbolic and Numerical Math in C++
                             -----------------

   Author:     Karl Rupp                          rupp@iue.tuwien.ac.at

   License:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/eval.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/diff.hpp"

template <typename E, typename T, typename U>
void operations_test(E & e, T const & t, U const & u, double t2, double u2)
{
  e = t + u; evaluations_test(e, t2 + u2);
  e = u + t; evaluations_test(e, u2 + t2);
  e = t - u; evaluations_test(e, t2 - u2);
  e = u - t; evaluations_test(e, u2 - t2);
  e = t * u; evaluations_test(e, t2 * u2);
  e = u * t; evaluations_test(e, u2 * t2);
  e = t / u; evaluations_test(e, t2 / u2);
  e = u / t; evaluations_test(e, u2 / t2);
}

template <typename E, typename T, typename U>
void operations_test(E & e, T const & t, U const & u)
{
  operations_test(e, t, u, viennamath::eval(t, viennamath::make_vector(4, 6, 8)), 
                           viennamath::eval(u, viennamath::make_vector(4, 6, 8)) );
}


template <typename E>
void evaluations_test(E & e, double ref_solution)
{
  viennamath::rt_constant<double> c4(4.0);
  viennamath::rt_constant<long> c6(6);
  viennamath::ct_constant<8> c8;

  std::vector<double> p(2);
  p[0] = 4;
  p[1] = 6;
  p[2] = 8;

  
  std::cout << e << " at STL (" << p[0] << ", " << p[1] << ", " << p[2] << ")"
            << " = " << e(p) 
            << " = " << viennamath::eval(e,p) 
            << " (reference solution: " << ref_solution << ")" << std::endl;
  assert(viennamath::eval(e, p) == ref_solution);
  
  std::cout << e << " at vector_3 (" << viennamath::make_vector(c4, c6, c8) << ")"
            << " = " << e(viennamath::make_vector(c4, c6, c8))
            << " = " << viennamath::eval(e, viennamath::make_vector(c4, c6, c8)) 
            << " (reference solution: " << ref_solution << ")" << std::endl;
  assert(viennamath::eval(e, viennamath::make_vector(c4, c6, c8)) == ref_solution);

}


template <typename E>
void unary_test(E const & e, double ref_solution)
{
  viennamath::rt_constant<double> c4(4.0);
  viennamath::rt_constant<long> c6(6);
  viennamath::ct_constant<8> c8;

  std::vector<double> p(2);
  p[0] = 4;
  p[1] = 6;
  p[2] = 8;
  
  std::cout << e << " at STL (" << p[0] << ", " << p[1] << ", " << p[2] << ")"
            << " = " << e(p) 
            << " = " << viennamath::eval(e,p) 
            << " (reference solution: " << ref_solution << ")" << std::endl;
  assert(viennamath::eval(e, p) == ref_solution);
  
  std::cout << e << " at vector_3 (" << viennamath::make_vector(c4, c6, c8) << ")"
            << " = " << e(viennamath::make_vector(c4, c6, c8))
            << " = " << viennamath::eval(e, viennamath::make_vector(c4, c6, c8)) 
            << " (reference solution: " << ref_solution << ")" << std::endl;
  assert(viennamath::eval(e, viennamath::make_vector(c4, c6, c8)) == ref_solution);
}

template <typename InterfaceType>
void unary_test(viennamath::rt_binary_expr<InterfaceType> const & e)
{
  std::vector<double> p(2);
  p[0] = 4;
  p[1] = 6;
  p[2] = 8;
  
  unary_test(viennamath::exp(e),   exp(viennamath::eval(e,p)) );
  unary_test(viennamath::sin(e),   sin(viennamath::eval(e,p)) );
  unary_test(viennamath::cos(e),   cos(viennamath::eval(e,p)) );
  unary_test(viennamath::tan(e),   tan(viennamath::eval(e,p)) );
  unary_test(viennamath::fabs(e),  fabs(viennamath::eval(e,p)) );
  unary_test(viennamath::sqrt(e),  sqrt(viennamath::eval(e,p)) );
  unary_test(viennamath::log(e),   log(viennamath::eval(e,p)) );
  unary_test(viennamath::log10(e), log10(viennamath::eval(e,p)) );
}





int main()
{
  viennamath::ct_variable<0> x;
  viennamath::ct_variable<1> y;
  viennamath::ct_variable<2> z;
  viennamath::rt_constant<double> c4(4.0);
  viennamath::rt_constant<long> c6(6);
  viennamath::ct_constant<8> c8;
  viennamath::expr e1 = x + y;
  viennamath::expr e2 = x*y+c8;
  viennamath::expr e3 = x/y-c8;
  viennamath::expr e;

  //compile time:
  std::cout << viennamath::diff(x+y, x) << std::endl;
  std::cout << viennamath::diff(x+y, y) << std::endl;
  std::cout << viennamath::diff(x+y, z) << std::endl;
  
  std::cout << viennamath::diff(x*y+c8, x) << std::endl;
  std::cout << viennamath::diff(x*y+c8, y) << std::endl;
  std::cout << viennamath::diff(x*y+c8, z) << std::endl;
  
  std::cout << viennamath::diff(x/y-c8, x) << std::endl;
  std::cout << viennamath::diff(x/y-c8, y) << std::endl;
  std::cout << viennamath::diff(x/y-c8, z) << std::endl;
  
  //run time:
  std::cout << viennamath::diff(e1, x) << std::endl;
  std::cout << viennamath::diff(e1, y) << std::endl;
  std::cout << viennamath::diff(e1, z) << std::endl;

  std::cout << viennamath::diff(e2, x) << std::endl;
  std::cout << viennamath::diff(e2, y) << std::endl;
  std::cout << viennamath::diff(e2, z) << std::endl;

  std::cout << viennamath::diff(e3, x) << std::endl;
  std::cout << viennamath::diff(e3, y) << std::endl;
  std::cout << viennamath::diff(e3, z) << std::endl;

  
  std::cout << viennamath::diff(viennamath::exp(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::exp(e1), x) << std::endl;

  std::cout << viennamath::diff(viennamath::sin(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::sin(e1), x) << std::endl;

  std::cout << viennamath::diff(viennamath::cos(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::cos(e1), x) << std::endl;
  
  std::cout << viennamath::diff(viennamath::tan(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::tan(e1), x) << std::endl;
  
  std::cout << viennamath::diff(viennamath::sqrt(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::sqrt(e1), x) << std::endl;
  
  std::cout << viennamath::diff(viennamath::log(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::log(e1), x) << std::endl;

  std::cout << viennamath::diff(viennamath::log10(x), x) << std::endl;
  std::cout << viennamath::diff(viennamath::log10(e1), x) << std::endl;
   

  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}