/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPR_OPERATIONS_CPP
#define VIENNAMATH_EXPR_OPERATIONS_CPP

#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/binary_expression.hpp"
#include "viennamath/unary_expression.hpp"
#include "viennamath/binary_operators.hpp"

namespace viennamath
{
  
  /////////////////////////////////// operator+ ///////////////////////////////////
  
  //with binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  //with self:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }
  
  //with expression:
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator+(ct_expr<LHS, OP, RHS> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with constant:
  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       constant<T, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator+(constant<T, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with ct_constant:
  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator+(ct_constant<value> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator+(variable<id, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }
  
  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(expr<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(default_numeric_type lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }










  /////////////////////////////////// operator- ///////////////////////////////////

  //with binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with self:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with expression:
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator-(ct_expr<LHS, OP, RHS> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with constant:
  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       constant<T, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator-(constant<T, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with ct_constant:
  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs));
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator-(ct_constant<value> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator-(variable<id, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(expr<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(default_numeric_type lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }










  /////////////////////////////////// operator* ///////////////////////////////////

  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  //with self:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  
  //with expression:
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator*(ct_expr<LHS, OP, RHS> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with constant:
  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       constant<T, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator*(constant<T, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with ct_constant:
  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs));
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator*(ct_constant<value> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator*(variable<id, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(expr<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(default_numeric_type lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }













  /////////////////////////////////// operator/ ///////////////////////////////////

  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with self:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.get()->clone());
  }
  
  //with expression:
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }
  
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> operator/(ct_expr<LHS, OP, RHS> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with constant:
  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       constant<T, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, typename T>
  binary_expr<InterfaceType> operator/(constant<T, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with ct_constant:
  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> operator/(ct_constant<value> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator/(variable<id, InterfaceType> const & lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(expr<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.get()->clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(default_numeric_type lhs,
                                       expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.get()->clone());
  }


}

#endif