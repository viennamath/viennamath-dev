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
#include "viennamath/unary_expression.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  struct Omega {};
  struct symbolic_tag {};
  
  expr integral(Omega, expr const & integrand, symbolic_tag)
  {
    return expr(new unary_expr(integrand.get()->clone(), new op_unary<op_symbolic_integration>()));
  }
  
  
}

#endif