
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/eval.hpp"
#include "viennamath/substitute.hpp"
#include "viennamath/diff.hpp"

#include "viennamath/equation.hpp"


std::vector<double> newton_solve_impl(std::vector<viennamath::equation> const & equations,
                                      std::vector<double> guess)
{
  viennamath::variable<0> x;
  viennamath::variable<1> y;

  //
  // Bring to form
  //   f1(x,y) = 0
  //   f2(x,y) = 0
  //
  viennamath::expr f1 = equations[0].lhs() - equations[0].rhs();
  viennamath::expr f2 = equations[1].lhs() - equations[1].rhs();
  
  // compute residuals:
  double res_f1 = f1(guess);
  double res_f2 = f2(guess);
  
  //
  // Entries of Jacobian matrix:
  //
  viennamath::expr df1_dx = viennamath::diff(f1, x);
  viennamath::expr df1_dy = viennamath::diff(f1, y);
  viennamath::expr df2_dx = viennamath::diff(f2, x);
  viennamath::expr df2_dy = viennamath::diff(f2, y);
  
  //std::cout << df1_dx << std::endl;
  //std::cout << df1_dy << std::endl;
  //std::cout << df2_dx << std::endl;
  //std::cout << df2_dy << std::endl;
  
  //TODO Solver for general linear system here
  
  //In the meanwhile, we use the solution formula for a 2-by-2 system:
  double det = df1_dx(guess) * df2_dy(guess) - df2_dx(guess) * df1_dy(guess);
  double update_x = (res_f1*df2_dy(guess) - df1_dy(guess)*res_f2) / det;
  double update_y = (df1_dx(guess)*res_f2 - res_f1*df2_dx(guess)) / det;
  
  std::vector<double> ret;
  ret.push_back( guess[0] - update_x );
  ret.push_back( guess[1] - update_y );
  
  return ret;
}

std::vector<double> newton_solve(std::vector<viennamath::equation> const & equations,
                                 std::vector<double> init_guess)
{
  viennamath::variable<0> x;
  viennamath::variable<1> y;
  double norm_res = 1;
  
  std::vector<double> x_k = init_guess;

  //
  // Bring to form
  //   f1(x,y) = 0
  //   f2(x,y) = 0
  //
  viennamath::expr f1 = equations[0].lhs() - equations[0].rhs();
  viennamath::expr f2 = equations[1].lhs() - equations[1].rhs();
  
  //iterate until convergence:
  while (norm_res > 1e-10 && norm_res < 1e10)
  {
    x_k = newton_solve_impl(equations, x_k);
    norm_res = ::sqrt(f1(x_k)*f1(x_k) + f2(x_k)*f2(x_k));
    std::cout << "Current x_k: (" << x_k[0] << ", " << x_k[1] << "), norm of residual: " << norm_res << std::endl;
 }
  
  
  return x_k;
}



int main()
{
  viennamath::variable<0> x;
  viennamath::variable<1> y;
  viennamath::variable<2> z;
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long> c6(6);
  viennamath::ct_constant<8> c8;
  viennamath::expr x_pow_4 = (x*x)*(x*x);

  //
  // Set up nonlinear system:
  //   x^2 + y   = 3.0
  //   x^4 - y^2 = 3.0
  // Solution is known to be (sqrt(2), 1)
  //
  std::vector<viennamath::equation> equ_system;
  equ_system.push_back(viennamath::make_equation(x*x + y, 3.0));
  equ_system.push_back(viennamath::make_equation(x_pow_4 - y*y, 3.0));
  
  //
  //Initial guess:
  //
  std::vector<double> init_guess;
  init_guess.push_back(1.0);
  init_guess.push_back(2.0);
  
  //
  // Launch Newton solver
  //
  std::vector<double> result = newton_solve(equ_system, init_guess);

  std::cout << "Result: (" << result[0] << ", " << result[1] << ")" << std::endl;
   

  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}