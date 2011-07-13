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
#include "viennamath/manipulation/integral.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/diff.hpp"
#include "viennamath/runtime/equation.hpp"
#include "viennamath/runtime/function_symbol.hpp"

namespace viennamath
{
  template <unsigned long dim>
  struct cartesian {};
  
  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<1>, expr<InterfaceType> const & ex)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    
    //replace grad:
    expr<InterfaceType> new_ex = ex;
    expr<InterfaceType> new_ex1(substitute(grad(u), diff(u, x), new_ex) );
    expr<InterfaceType> new_ex2(substitute(grad(v), diff(v, x), new_ex1) );
    
    //replace div:
    expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x), new_ex2) );
    expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x), new_ex3) );
    
    return new_ex4;
  }

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<1>, unary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<1>(), temp);
  }

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<1>, binary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<1>(), temp);
  }
  
  
  /********* 2d *********/

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<2>, expr<InterfaceType> const & ex)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    variable<InterfaceType> y(1);
    
    //TODO: This does not work like this!! Gradient needs to return a vector-expression!
    //replace grad:
    expr<InterfaceType> new_ex = ex;
    expr<InterfaceType> new_ex1(substitute(grad(u), diff(u, x), new_ex) );
    expr<InterfaceType> new_ex2(substitute(grad(v), diff(v, x), new_ex1) );
    
    //replace div:
    expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x) + diff(u, y), new_ex2) );
    expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x) + diff(v, y), new_ex3) );
    
    return new_ex4;
  }
  
  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<2>, unary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<2>(), temp);
  }

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<2>, binary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<2>(), temp);
  }


  /******** 3d ***********/

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<3>, expr<InterfaceType> const & ex)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    variable<InterfaceType> y(1);
    variable<InterfaceType> z(2);
    
    //TODO: This does not work like this!! Gradient needs to return a vector-expression!
    //replace grad:
    expr<InterfaceType> new_ex = ex;
    expr<InterfaceType> new_ex1(substitute(grad(u), diff(u, x), new_ex) );
    expr<InterfaceType> new_ex2(substitute(grad(v), diff(v, x), new_ex1) );
    
    //replace div:
    expr<InterfaceType> new_ex3(substitute(div(u), diff(u, x) + diff(u, y) + diff(u, z), new_ex2) );
    expr<InterfaceType> new_ex4(substitute(div(v), diff(v, x) + diff(v, y) + diff(v, z), new_ex3) );
    
    return new_ex4;
  }
  
  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<3>, unary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<3>(), temp);
  }

  template <typename InterfaceType>
  expr<InterfaceType> apply_coordinate_system(cartesian<3>, binary_expr<InterfaceType> const & ex)
  {
    expr<InterfaceType> temp(ex);
    return apply_coordinate_system(cartesian<3>(), temp);
  }
  
  
  //TODO: more and better compile time derivation
  
  
  
  


  //tries to automatically derive the weak formulation from the strong formulation
  template <typename InterfaceType>
  equation<InterfaceType> apply_coordinate_system(cartesian<1>,
                                                  equation<InterfaceType> const & equ)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    
    //TODO: More general applications -> requires vector of expressions
    expr<InterfaceType> new_lhs(substitute( grad(u) * grad(v),
                                            diff(u, x) * diff(v, x),
                                            equ.lhs()
                                          )
                               );
    return equation<InterfaceType>( new_lhs,
                                    equ.rhs()
                                  );
  }


  template <typename InterfaceType>
  equation<InterfaceType> apply_coordinate_system(cartesian<2>,
                                                  equation<InterfaceType> const & equ)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    variable<InterfaceType> y(1);
    
    //TODO: More general applications -> requires vector of expressions
    expr<InterfaceType> new_lhs(substitute( grad(u) * grad(v),
                                            diff(u, x) * diff(v, x) + diff(u, y) * diff(v, y),
                                            equ.lhs()
                                          )
                               );
    return equation<InterfaceType>( new_lhs,
                                    equ.rhs()
                                  );
  }

  template <typename InterfaceType>
  equation<InterfaceType> apply_coordinate_system(cartesian<3>,
                                                  equation<InterfaceType> const & equ)
  {
    function_symbol<InterfaceType> u(0, unknown_tag<>());
    function_symbol<InterfaceType> v(0, test_tag<>());
    variable<InterfaceType> x(0);
    variable<InterfaceType> y(1);
    variable<InterfaceType> z(2);
    
    //TODO: More general applications -> requires vector of expressions
    expr<InterfaceType> new_lhs(substitute( grad(u) * grad(v),
                                            diff(u, x) * diff(v, x) + diff(u, y) * diff(v, y) + diff(u, z) * diff(v, z),
                                            equ.lhs()
                                          )
                               );
    return equation<InterfaceType>( new_lhs,
                                    equ.rhs()
                                  );
  }

}

#endif