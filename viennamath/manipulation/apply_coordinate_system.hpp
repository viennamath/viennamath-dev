/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_APPLY_COORDINATE_SYSTEM_HPP
#define VIENNAMATH_APPLY_COORDINATE_SYSTEM_HPP

#include "viennamath/forwards.h"
#include "viennamath/manipulation/unary_operators_manipulation.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/diff.hpp"
#include "viennamath/runtime/equation.hpp"
#include "viennamath/runtime/function_symbol.hpp"

namespace viennamath
{
  template <id_type dim>
  struct cartesian {};
  
  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<1>, rt_expr<InterfaceType> const & ex)
  {
    rt_function_symbol<InterfaceType> u(0, unknown_tag<>());
    rt_function_symbol<InterfaceType> v(0, test_tag<>());
    rt_variable<InterfaceType> x(0);
    
    //replace grad:
    rt_expr<InterfaceType> new_ex = ex;
    rt_expr<InterfaceType> new_ex1(substitute(grad(u), diff(u, x), new_ex) );
    rt_expr<InterfaceType> new_ex2(substitute(grad(v), diff(v, x), new_ex1) );
    
    //replace div:
    rt_expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x), new_ex2) );
    rt_expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x), new_ex3) );
    
    return new_ex4;
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<1>, rt_unary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<1>(), temp);
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<1>, rt_binary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<1>(), temp);
  }
  
  
  /********* 2d *********/

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<2>, rt_expr<InterfaceType> const & ex)
  {
    rt_function_symbol<InterfaceType> u(0, unknown_tag<>());
    rt_function_symbol<InterfaceType> v(0, test_tag<>());
    rt_variable<InterfaceType> x(0);
    rt_variable<InterfaceType> y(1);
    
    rt_vector_expr<InterfaceType> grad_u(2);
    grad_u[0] = diff(u, x);
    grad_u[1] = diff(u, y);

    rt_vector_expr<InterfaceType> grad_v(2);
    grad_v[0] = diff(v, x);
    grad_v[1] = diff(v, y);
    
    //replace grad:
    rt_expr<InterfaceType> new_ex1(substitute(grad(u), grad_u, ex) );
    rt_expr<InterfaceType> new_ex2(substitute(grad(v), grad_v, new_ex1) );
    
    //replace div:
    rt_expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x) + diff(u, y), new_ex2) );
    rt_expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x) + diff(v, y), new_ex3) );
    
    return new_ex4;
  }
  
  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<2>, rt_unary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<2>(), temp);
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<2>, rt_binary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<2>(), temp);
  }


  /******** 3d ***********/

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<3>, rt_expr<InterfaceType> const & ex)
  {
    rt_function_symbol<InterfaceType> u(0, unknown_tag<>());
    rt_function_symbol<InterfaceType> v(0, test_tag<>());
    rt_variable<InterfaceType> x(0);
    rt_variable<InterfaceType> y(1);
    rt_variable<InterfaceType> z(2);
    
    rt_vector_expr<InterfaceType> grad_u(3);
    grad_u[0] = diff(u, x);
    grad_u[1] = diff(u, y);
    grad_u[2] = diff(u, z);

    rt_vector_expr<InterfaceType> grad_v(3);
    grad_v[0] = diff(v, x);
    grad_v[1] = diff(v, y);
    grad_v[2] = diff(v, z);
    
    //replace grad:
    rt_expr<InterfaceType> new_ex1(substitute(grad(u), grad_u, ex) );
    rt_expr<InterfaceType> new_ex2(substitute(grad(v), grad_v, new_ex1) );
    
    //replace div:
    rt_expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x) + diff(u, y) + diff(u, z), new_ex2) );
    rt_expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x) + diff(v, y) + diff(v, z), new_ex3) );
    
    return new_ex4;
  }
  
  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<3>, rt_unary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<3>(), temp);
  }

  template <typename InterfaceType>
  rt_expr<InterfaceType> apply_coordinate_system(cartesian<3>, rt_binary_expr<InterfaceType> const & ex)
  {
    rt_expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<3>(), temp);
  }
  
  
  //TODO: more and better compile time derivation
  
  
  
  


  //tries to automatically derive the weak formulation from the strong formulation
  template <typename InterfaceType, id_type dim>
  rt_equation<InterfaceType> apply_coordinate_system(cartesian<dim>,
                                                     rt_equation<InterfaceType> const & equ)
  {
    return rt_equation<InterfaceType>( apply_coordinate_system(cartesian<dim>(), equ.lhs()),
                                       apply_coordinate_system(cartesian<dim>(), equ.rhs())
                                     );
  }

}

#endif