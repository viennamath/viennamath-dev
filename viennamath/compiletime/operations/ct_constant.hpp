/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_CONSTANT_OPERATIONS_HPP
#define VIENNAMATH_CT_CONSTANT_OPERATIONS_HPP

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
  ct_expr<rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >,
              op_plus<default_numeric_type>,
              RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_expr<rt_constant<ScalarType>, op_plus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_expr<result_constant,
                      op_plus<default_numeric_type>,
                      RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 + X) -> [ct_c1 + ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_expr<ct_constant<value + value2>,
            op_plus<default_numeric_type>,
            RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_expr<ct_constant<value2>, op_plus<default_numeric_type>, RHS> const & other)
  {
    return ct_expr<ct_constant<value + value2>,
                      op_plus<default_numeric_type>,
                      RHS >(ct_constant<value + value2>(), other.rhs());
  }
  
  // ct_c1 + (c2 - X)    -> [ct_c1 + c2]    - X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_expr<rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >,
              op_minus<default_numeric_type>,
              RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_expr<rt_constant<ScalarType>, op_minus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_plus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_expr<result_constant,
                      op_minus<default_numeric_type>,
                      RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 - X) -> [ct_c1 + ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_expr<ct_constant<value + value2>,
            op_minus<default_numeric_type>,
            RHS >
  operator+(ct_constant<value> const & lhs, 
            ct_expr<ct_constant<value2>, op_minus<default_numeric_type>, RHS> const & other)
  {
    return ct_expr<ct_constant<value + value2>,
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
  ct_expr<rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >,
              op_minus<default_numeric_type>,
              RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_expr<rt_constant<ScalarType>, op_plus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_expr<result_constant,
                      op_minus<default_numeric_type>,
                      RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 + X) -> [ct_c1 - ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_expr<ct_constant<value - value2>,
            op_minus<default_numeric_type>,
            RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_expr<ct_constant<value2>, op_plus<default_numeric_type>, RHS> const & other)
  {
    return ct_expr<ct_constant<value - value2>,
                      op_minus<default_numeric_type>,
                      RHS >(ct_constant<value - value2>(), other.rhs());
  }
  
  // ct_c1 - (c2 - X)    -> [ct_c1 - c2] + X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  ct_expr<rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >,
              op_plus<default_numeric_type>,
              RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_expr<rt_constant<ScalarType>, op_minus<default_numeric_type>, RHS> const & other)
  {
    typedef rt_constant< typename promote_traits<long, op_minus<default_numeric_type>, ScalarType>::result_type >   result_constant;
    return ct_expr<result_constant,
                      op_plus<default_numeric_type>,
                      RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 - X) -> [ct_c1 - ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  ct_expr<ct_constant<value - value2>,
            op_plus<default_numeric_type>,
            RHS >
  operator-(ct_constant<value> const & lhs, 
            ct_expr<ct_constant<value2>, op_minus<default_numeric_type>, RHS> const & other)
  {
    return ct_expr<ct_constant<value - value2>,
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