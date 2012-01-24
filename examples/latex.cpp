
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/latex.hpp"
#include "viennamath/manipulation/diff.hpp"

//
// Testing functors on expression tree
//




int main()
{
  viennamath::variable x(0);
  viennamath::variable y(1);
  viennamath::variable z(2);
  viennamath::rt_constant<double> c4(4.0);
  viennamath::rt_constant<long> c6(6);
  viennamath::function_symbol u(0, viennamath::unknown_tag<>());
  viennamath::function_symbol v(0, viennamath::test_tag<>());

  
  viennamath::expr e1 = x + viennamath::diff(u, x) + viennamath::tan(y) - viennamath::exp(z);
  viennamath::expr e2 = viennamath::log(viennamath::sin(viennamath::sqrt(x/c4) + viennamath::log10(z)) + viennamath::cos(y)) 
                        + viennamath::fabs(x/y) 
                        + viennamath::grad(u) * viennamath::grad(v);
  viennamath::equation eq(e1, e2);
  
  viennamath::latex_translator  to_latex;
  to_latex.customize(u, "u");
  to_latex.customize(v, "v");
  to_latex.customize(x, "x");
  to_latex.customize(y, "y");
  to_latex.customize(z, "z");
  
  std::cout << "e1: " << to_latex(e1) << std::endl;
  std::cout << "e2: " << to_latex(e2) << std::endl;
  std::cout << "eq: " << to_latex(eq) << std::endl;
  
  return EXIT_SUCCESS;
}