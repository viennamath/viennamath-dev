/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_INTEGRAL_HPP
#define VIENNAMATH_INTEGRAL_HPP

#include "viennamath/forwards.h"
#include "viennamath/runtime/unary_expression.hpp"
#include "viennamath/compiletime/unary_op_tags.hpp"

namespace viennamath
{
  struct Omega {};
  struct symbolic_tag {};
  
  template <typename InterfaceType>
  expr<InterfaceType> integral(Omega, expr<InterfaceType> const & integrand, symbolic_tag)
  {
    return expr<InterfaceType>(new unary_expr<InterfaceType>(integrand.get()->clone(),
                                                             new op_unary<op_symbolic_integration<typename InterfaceType::numeric_type>, InterfaceType>())
                              );
  }
  
  template <typename InterfaceType>
  expr<InterfaceType> integral(Omega, binary_expr<InterfaceType> const & integrand, symbolic_tag)
  {
    return expr<InterfaceType>(new unary_expr<InterfaceType>(integrand.clone(),
                                                             new op_unary<op_symbolic_integration<typename InterfaceType::numeric_type>, InterfaceType>())
                              );
  }
  
}

#endif