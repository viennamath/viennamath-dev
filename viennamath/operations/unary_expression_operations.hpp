/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNARY_EXPRESSION_OPERATIONS_CPP
#define VIENNAMATH_UNARY_EXPRESSION_OPERATIONS_CPP

#include "viennamath/forwards.h"
#include "viennamath/compiletime/ct_expr.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/runtime/binary_operators.hpp"

namespace viennamath
{
  
  /////////////////////////////////// operator+ ///////////////////////////////////
  
  //with other unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(unary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  

  /////////////////////////////////// operator- ///////////////////////////////////

  //with other unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(unary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(unary_expr<InterfaceType> const & lhs, default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  /////////////////////////////////// operator* ///////////////////////////////////
  
  //with other unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(unary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }


  /////////////////////////////////// operator/ ///////////////////////////////////

  //with other unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(unary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

}

#endif