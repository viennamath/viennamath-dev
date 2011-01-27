
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/eval.hpp"
#include "viennamath/ct_eval.hpp"


template <typename T, typename U>
void operations_test(T const & t, U const & u, double t2, double u2)
{
  std::cout << "LHS: " << t << ", RHS: " << u << std::endl; 
  evaluations_test(t + u, t2 + u2);
  evaluations_test(u + t, u2 + t2);
  evaluations_test(t - u, t2 - u2);
  evaluations_test(u - t, u2 - t2);
  evaluations_test(t * u, t2 * u2);
  evaluations_test(u * t, u2 * t2);
  evaluations_test(t / u, t2 / u2);
  evaluations_test(u / t, u2 / t2);
}


template <typename T, typename U>
void operations_test(T const & t, U const & u)
{
  operations_test(t, u, viennamath::eval(t, viennamath::make_vector(4, 6, 8)), 
                        viennamath::eval(u, viennamath::make_vector(4, 6, 8)) );
}


template <typename E>
void evaluations_test(E const & e, double ref_solution)
{
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);
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



int main()
{
  viennamath::variable<0> x;
  viennamath::variable<1> y;
  viennamath::variable<2> z;
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);
  viennamath::ct_constant<8> c8;
  
  std::vector<double> p(2);
  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  
  std::cout << "--- Involved types ---" << std::endl;
  std::cout << "x: " << x << std::endl;
  std::cout << "y: " << y << std::endl;
  std::cout << "z: " << z << std::endl;
  std::cout << "c4: " << c4 << std::endl;
  std::cout << "c6: " << c6 << std::endl;
  std::cout << "c8: " << c8 << std::endl;

  std::cout << "--- Various expressions: ---" << std::endl;
  operations_test(x,x);
  operations_test(x,x + y);
  operations_test(x,c4);
  operations_test(x,c4 + y);
  operations_test(x,c6);
  operations_test(x,c6 + y);
  operations_test(x,c8);
  operations_test(x,c8 + y);

  operations_test(x+y,x);
  operations_test(x+y,x + y);
  operations_test(x+y,c4);
  operations_test(x+y,c4 + y);
  operations_test(x+y,c6);
  operations_test(x+y,c6 + y);
  operations_test(x+y,c8);
  operations_test(x+y,c8 + y);

  operations_test(c4,x);
  operations_test(c4,x + y);
  operations_test(c4,c4);
  operations_test(c4,c4 + y);
  operations_test(c4,c6);
  operations_test(c4,c6 + y);
  operations_test(c4,c8);
  operations_test(c4,c8 + y);
  
  operations_test(c4+y,x);
  operations_test(c4+y,x + y);
  operations_test(c4+y,c4);
  operations_test(c4+y,c4 + y);
  operations_test(c4+y,c6);
  operations_test(c4+y,c6 + y);
  operations_test(c4+y,c8);
  operations_test(c4+y,c8 + y);
  
  operations_test(c6,x);
  operations_test(c6,x + y);
  operations_test(c6,c4);
  operations_test(c6,c4 + y);
  operations_test(c6,c4 - y);
  operations_test(c6,y + c4);
  operations_test(c6,y - c4);
  operations_test(c6,c6);
  operations_test(c6,c6 + y);
  operations_test(c6,c6 - y);
  operations_test(c6,c8);
  operations_test(c6,c8 + y);
  
  operations_test(c6+y,x);
  operations_test(c6+y,x + y);
  operations_test(c6+y,c4);
  operations_test(c6+y,c4 + y);
  operations_test(c6+y,c6);
  operations_test(c6+y,c6 + y);
  operations_test(c6+y,c8);
  operations_test(c6+y,c8 + y);
  
  operations_test(c8,x);
  operations_test(c8,x + y);
  operations_test(c8,c4);
  operations_test(c8,c4 + y);
  operations_test(c8,c4 - y);
  operations_test(c8,y + c4);
  operations_test(c8,y - c4);
  operations_test(c8,c6);
  operations_test(c8,c6 + y);
  operations_test(c8,c6 - y);
  operations_test(c8,c8);
  operations_test(c8,c8 + y);  
  
  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}