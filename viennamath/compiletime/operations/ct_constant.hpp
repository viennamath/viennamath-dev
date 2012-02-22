#ifndef VIENNAMATH_COMPILETIME_OPERATIONS_CT_CONSTANT_HPP
#define VIENNAMATH_COMPILETIME_OPERATIONS_CT_CONSTANT_HPP

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




#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/compiletime/ct_constant.hpp"

namespace viennamath
{
      
  ////////////////// Operations //////////////////////////////
  
  //operator+

  // ct_c1 + (c2 + X) -> [ct_c1 + c2] + X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_binary_expr<rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >,
                 op_plus<default_numeric_type>,
                 RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_binary_expr<rt_constant<ScalarType>, op_plus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_binary_expr<result_constant,
                          op_plus<default_numeric_type>,
                          RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 + X) -> [ct_c1 + ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_binary_expr<ct_constant<value + value2>,
                 op_plus<default_numeric_type>,
                 RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_binary_expr<ct_constant<value2>, op_plus<default_numeric_type>, RHS> const & other)
  {
    return ct_binary_expr<ct_constant<value + value2>,
                          op_plus<default_numeric_type>,
                          RHS >(ct_constant<value + value2>(), other.rhs());
  }
  
  // ct_c1 + (c2 - X)    -> [ct_c1 + c2]    - X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_binary_expr<rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >,
                 op_minus<default_numeric_type>,
                 RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_binary_expr<rt_constant<ScalarType>, op_minus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_binary_expr<result_constant,
                          op_minus<default_numeric_type>,
                          RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 - X) -> [ct_c1 + ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_binary_expr<ct_constant<value + value2>,
                 op_minus<default_numeric_type>,
                 RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_binary_expr<ct_constant<value2>, op_minus<default_numeric_type>, RHS> const & other)
  {
    return ct_binary_expr<ct_constant<value + value2>,
                          op_minus<default_numeric_type>,
                          RHS >(ct_constant<value + value2>(), other.rhs());
  }
  
  template <long value, long other_value>
  ct_constant<value + other_value>
  operator+(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value + other_value>();
  }


  //operator-
  
  // ct_c1 - (c2 + X) -> [ct_c1 - c2] - X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_binary_expr<rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >,
                 op_minus<default_numeric_type>,
                 RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_binary_expr<rt_constant<ScalarType>, op_plus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_binary_expr<result_constant,
                          op_minus<default_numeric_type>,
                          RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 + X) -> [ct_c1 - ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_binary_expr<ct_constant<value - value2>,
                 op_minus<default_numeric_type>,
                 RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_binary_expr<ct_constant<value2>, op_plus<default_numeric_type>, RHS> const & other)
  {
    return ct_binary_expr<ct_constant<value - value2>,
                          op_minus<default_numeric_type>,
                          RHS >(ct_constant<value - value2>(), other.rhs());
  }
  
  // ct_c1 - (c2 - X)    -> [ct_c1 - c2] + X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_binary_expr<rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >,
                 op_plus<default_numeric_type>,
                 RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_binary_expr<rt_constant<ScalarType>, op_minus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_binary_expr<result_constant,
                          op_plus<default_numeric_type>,
                          RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 - X) -> [ct_c1 - ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_binary_expr<ct_constant<value - value2>,
                 op_plus<default_numeric_type>,
                 RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_binary_expr<ct_constant<value2>, op_minus<default_numeric_type>, RHS> const & other)
  {
    return ct_binary_expr<ct_constant<value - value2>,
                          op_plus<default_numeric_type>,
                          RHS >(ct_constant<value - value2>(), other.rhs());
  }
  
  
  template <long value, long other_value>
  ct_constant<value - other_value>
  operator-(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value - other_value>();
  }


  //operator*

  template <long value, long other_value>
  ct_constant<value * other_value>
  operator*(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value * other_value>();
  }


  //operator/
  
  // (none so far)
  
}

#endif