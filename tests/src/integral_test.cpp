
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
//#include "viennamath/manipulation/integral.hpp"
#include "viennamath/runtime/numerical_quadrature.hpp"



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
  viennamath::expr e4 = x + c8;

  
  viennamath::interval rt_int01(0, 1);
  std::cout << "Interval: " << rt_int01 << std::endl;

  viennamath::interval rt_intxy(x, y);
  std::cout << "Interval: " << rt_intxy << std::endl;

  viennamath::ct_interval<viennamath::ct_constant<0>,
                          viennamath::ct_constant<1> > ct_int01;
  std::cout << "Interval: " << ct_int01 << std::endl;
  
  viennamath::ct_interval<viennamath::ct_variable<0>,
                          viennamath::ct_variable<1> > ct_intxy;
  std::cout << "Interval: " << ct_intxy << std::endl;

  //////////////////////
  
  viennamath::expr e4_int = viennamath::integral( viennamath::interval(0, 1), e4, x );
  
  std::cout << "Integral: " << e4_int << std::endl;
  
  std::cout << "Starting evaluation..." << std::endl;
  viennamath::numerical_quadrature integrator(new viennamath::gauss_quad_1());
  std::cout << "Evaluated, type 1: " << integrator(e4_int) << std::endl;
  std::cout << "Evaluated, type 2a: " << integrator(viennamath::interval(0, 1), e4, x) << std::endl;

  std::cout << std::endl;
  viennamath::expr my_integral = viennamath::integral(viennamath::symbolic_interval(), e4);
  std::cout << "Symbolic integral: " << my_integral << std::endl;
  
  viennamath::expr my_integral2 = viennamath::substitute(viennamath::symbolic_interval(),
                                                         std::make_pair(viennamath::interval(0, 1), x),
                                                         my_integral);
  std::cout << "Symbolic integral, substituted: " << my_integral2 << std::endl;
  
  
  
  
/*  
  viennamath::interval int01(0,1);
  viennamath::ct_interval<0,1> ct_int01;
  
  
  viennamath::numerical_integrator gauss_integrator(viennamath::GAUSS);
  viennamath::symbolic_integrator symb_integrator(rt_gauss_quad(5));
  
  // numerical quadrature (no copy of e2)
  viennamath::expr e = gauss_integrator( viennamath::rt_interval(0, 1),
                                         e2,
                                         x );
  
  // Analytical integration
  viennamath::expr e = symb_integrator( viennamath::rt_interval(0, 1),
                                        e2,
                                        x );

  // Just represent the integral, no evaluation:
  viennamath::expr e = viennamath::integral( viennamath::rt_interval(0, 1),
                                             e2,
                                             x );
  double result = gauss_integrator(e);   //now integrate it
  
  // pure representation of an integral about something (no second and third argument)
  viennamath::expr e_symb = viennamath::integral( viennamath::rt_symbolic_interval(id),
                                                  e2);
  
  // NOT GOOD: unintuitive
  //viennamath::expr e = viennamath::integral(viennamath::rt_interval(0, 1), e_symb, x); //replace symbolic_interval by interval (0,1) with respect to x.
  
  viennamath::expr e = replace_integration_domain(viennamath::rt_symbolic_interval(id),
                                                  viennamath::rt_interval(0, 1),
                                                  x,
                                                  e2);

  // multiple integrals
  viennamath::expr e = replace_integration_domain(viennamath::rt_symbolic_interval(id),
                                                  make_vector(viennamath::rt_interval(0, 1), viennamath::rt_interval(0, 1), viennamath::rt_interval(0, 1)),
                                                  make_vector(x, y, z),
                                                  e2);
  
*/
  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}