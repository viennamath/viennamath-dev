/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_RUN_TIME_OPERATIONS_CPP
#define VIENNAMATH_EXPRESSION_RUN_TIME_OPERATIONS_CPP

#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/expression_run_time.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  expr operator+(expr const & lhs, expr const & rhs)
  {
    return expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }
  
}

#endif