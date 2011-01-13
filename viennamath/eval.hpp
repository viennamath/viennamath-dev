/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EVAL_HPP
#define VIENNAMATH_EVAL_HPP

#include "viennamath/forwards.h"
#include "viennamath/expression_run_time_operations.hpp"

namespace viennamath
{
  template <typename ExpressionType, typename VectorType>
  numeric_type eval(ExpressionType const & e, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return e(v);
  }

  template <typename VectorType>
  numeric_type eval(numeric_type value, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return value;
  }

  template <typename VectorType>
  long eval(long value, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return value;
  }

  template <typename VectorType>
  long eval(constant<long> c, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return c();
  }

  template <long value, typename VectorType>
  long eval(ct_constant<value> c, VectorType const & v)
  {
    //generic approach: use operator() and hope the best:
    return value;
  }

  template <typename VectorType>
  numeric_type eval(expr const & e, VectorType const & v)
  {
    //we have unwrap the runtime expression:
    return e(v).unwrap();
  }

}

#endif