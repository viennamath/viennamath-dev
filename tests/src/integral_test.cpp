
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/eval.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/diff.hpp"
#include "viennamath/manipulation/integrate.hpp"



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

  viennamath::interval int01(0,1);
  viennamath::ct_interval<0,1> ct_int01;
  
  
  viennamath::numerical_integrator gauss_integrator(viennamath::GAUSS);
  viennamath::symbolic_integrator symb_integrator(rt_gauss_quad(5));
  
  // numerical quadrature
  viennamath::expr e = gauss_integrator( viennamath::rt_interval(0, 1),
                                         e2,
                                         x );
  
  // Analytical integration
  viennamath::expr e = symb_integrator( viennamath::rt_interval(0, 1),
                                        e2,
                                        x );
   
  // pure representation of an integral about something (no second and third argument)
  viennamath::expr e_symb = viennamath::integral( viennamath::rt_symbolic_interval(id),
                                                  e2);
  
  // NOT GOOD: unintuitive
  //viennamath::expr e = viennamath::integral(viennamath::rt_interval(0, 1), e_symb, x); //replace symbolic_interval by interval (0,1) with respect to x.
  
  viennamath::expr e = replace_integration_domain(viennamath::rt_symbolic_interval(id),
                                                  viennamath::rt_interval(0, 1),
                                                  x,
                                                  e);
  

  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}