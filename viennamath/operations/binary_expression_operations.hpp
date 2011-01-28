/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_BINARY_EXPRESSION_OPERATIONS_CPP
#define VIENNAMATH_BINARY_EXPRESSION_OPERATIONS_CPP

#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/binary_expression.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  
  /////////////////////////////////// operator+ ///////////////////////////////////
  
  //with other binary expression:
  binary_expr operator+(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }
  
  //with unary expression:
  binary_expr operator+(binary_expr const & lhs, unary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator+(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator+(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator+(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  template <typename T>
  binary_expr operator+(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator+(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator+(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  //with variable:
  template <unsigned long id>
  binary_expr operator+(binary_expr const & lhs, variable<id> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }

  template <unsigned long id>
  binary_expr operator+(variable<id> const & lhs, binary_expr const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr(lhs.clone(), new op_plus(), rhs.clone());
  }
  
  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator+(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), new op_plus(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator+(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), new op_plus(), rhs.clone());
  }

  /////////////////////////////////// operator- ///////////////////////////////////

  //with other binary expression:
  binary_expr operator-(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }
  
  //with unary expression:
  binary_expr operator-(binary_expr const & lhs, unary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator-(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator-(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator-(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  template <typename T>
  binary_expr operator-(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator-(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator-(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  //with variable:
  template <unsigned long id>
  binary_expr operator-(binary_expr const & lhs, variable<id> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  template <unsigned long id>
  binary_expr operator-(variable<id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator-(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), new op_minus(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator-(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), new op_minus(), rhs.clone());
  }


  /////////////////////////////////// operator* ///////////////////////////////////

  //with other binary expression:
  binary_expr operator*(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }
  
  //with unary expression:
  binary_expr operator*(binary_expr const & lhs, unary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator*(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator*(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator*(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  template <typename T>
  binary_expr operator*(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator*(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator*(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  //with variable:
  template <unsigned long id>
  binary_expr operator*(binary_expr const & lhs, variable<id> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  template <unsigned long id>
  binary_expr operator*(variable<id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator*(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), new op_mult(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator*(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), new op_mult(), rhs.clone());
  }




  /////////////////////////////////// operator/ ///////////////////////////////////

  //with other binary expression:
  binary_expr operator/(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }
  
  //with unary expression:
  binary_expr operator/(binary_expr const & lhs, unary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator/(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator/(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator/(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  template <typename T>
  binary_expr operator/(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator/(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator/(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  //with variable:
  template <unsigned long id>
  binary_expr operator/(binary_expr const & lhs, variable<id> const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  template <unsigned long id>
  binary_expr operator/(variable<id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator/(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), new op_div(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator/(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), new op_div(), rhs.clone());
  }


}

#endif