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
  
  //with other expression:
  binary_expr operator+(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator+(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator+(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator+(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  template <typename T>
  binary_expr operator+(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator+(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator+(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  //with unknown:
  template <typename T, unsigned long id>
  binary_expr operator+(binary_expr const & lhs, unknown<T, id> const & rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }

  template <typename T, unsigned long id>
  binary_expr operator+(unknown<T, id> const & lhs, binary_expr const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr(lhs.clone(), op_plus().clone(), rhs.clone());
  }
  
  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator+(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), op_plus().clone(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator+(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), op_plus().clone(), rhs.clone());
  }

  /////////////////////////////////// operator- ///////////////////////////////////

  //with other expression:
  binary_expr operator-(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator-(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator-(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator-(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  template <typename T>
  binary_expr operator-(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator-(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator-(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  //with unknown:
  template <typename T, unsigned long id>
  binary_expr operator-(binary_expr const & lhs, unknown<T, id> const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  template <typename T, unsigned long id>
  binary_expr operator-(unknown<T, id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator-(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), op_minus().clone(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator-(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), op_minus().clone(), rhs.clone());
  }


  /////////////////////////////////// operator* ///////////////////////////////////

  //with other expression:
  binary_expr operator*(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator*(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator*(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator*(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  template <typename T>
  binary_expr operator*(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator*(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator*(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  //with unknown:
  template <typename T, unsigned long id>
  binary_expr operator*(binary_expr const & lhs, unknown<T, id> const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  template <typename T, unsigned long id>
  binary_expr operator*(unknown<T, id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator*(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), op_mult().clone(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator*(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), op_mult().clone(), rhs.clone());
  }




  /////////////////////////////////// operator/ ///////////////////////////////////

  //with other expression:
  binary_expr operator/(binary_expr const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator/(binary_expr const & lhs, expression<LHS, OP, RHS> const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }
  
  template <typename LHS, typename OP, typename RHS>
  binary_expr operator/(expression<LHS, OP, RHS> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  //with constant:
  template <typename T>
  binary_expr operator/(binary_expr const & lhs, constant<T> const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  template <typename T>
  binary_expr operator/(constant<T> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  //with ct_constant:
  template <unsigned long value>
  binary_expr operator/(binary_expr const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  template <unsigned long value>
  binary_expr operator/(ct_constant<value> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  //with unknown:
  template <typename T, unsigned long id>
  binary_expr operator/(binary_expr const & lhs, unknown<T, id> const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  template <typename T, unsigned long id>
  binary_expr operator/(unknown<T, id> const & lhs, binary_expr const & rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  binary_expr operator/(binary_expr const & lhs, numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(), op_div().clone(), constant<numeric_type>(rhs.get()).clone());
  }

  binary_expr operator/(numeric_type_proxy lhs, binary_expr const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(), op_div().clone(), rhs.clone());
  }


}

#endif