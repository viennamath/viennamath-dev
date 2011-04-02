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
#include "viennamath/compiletime/ct_expr.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/runtime/binary_operators.hpp"

namespace viennamath
{
  
  /////////////////////////////////// operator+ ///////////////////////////////////
  
  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator+(ct_expr<LHS, OP, RHS> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new binary_expr<InterfaceType>(lhs),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with constant:
  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, constant<T> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator+(constant<T> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_constant:
  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator+(ct_constant<value> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<long, InterfaceType>(value),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with variable:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(variable<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, ct_variable<id> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator+(ct_variable<id> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator+(binary_expr<InterfaceType> const & lhs, numeric_type_proxy<NumericT> rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), constant<NumericT>(rhs.get()).clone());
  }

  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator+(numeric_type_proxy<NumericT> lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(constant<NumericT>(lhs.get()).clone(), new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  /////////////////////////////////// operator- ///////////////////////////////////

  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator-(ct_expr<LHS, OP, RHS> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new binary_expr<InterfaceType>(lhs),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with constant:
  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, constant<T> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator-(constant<T> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_constant:
  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator-(ct_constant<value> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<long, InterfaceType>(value),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with variable:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(variable<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, ct_variable<id> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator-(ct_variable<id> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator-(binary_expr<InterfaceType> const & lhs, numeric_type_proxy<NumericT> rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), constant<NumericT>(rhs.get()).clone());
  }

  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator-(numeric_type_proxy<NumericT> lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(constant<NumericT>(lhs.get()).clone(), new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }


  /////////////////////////////////// operator* ///////////////////////////////////

  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with expression:
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator*(ct_expr<LHS, OP, RHS> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new binary_expr<InterfaceType>(lhs),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with constant:
  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, constant<T> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator*(constant<T> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_constant:
  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), 
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator*(ct_constant<value> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<long, InterfaceType>(value),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with variable:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(variable<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, ct_variable<id> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator*(ct_variable<id> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator*(binary_expr<InterfaceType> const & lhs, numeric_type_proxy<NumericT> rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), constant<NumericT>(rhs.get()).clone());
  }

  template <typename InterfaceType, typename NumericT>
  binary_expr<InterfaceType> operator*(numeric_type_proxy<NumericT> lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(constant<NumericT>(lhs.get()).clone(), new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }




  /////////////////////////////////// operator/ ///////////////////////////////////

  //with other binary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  //with unary expression:
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, unary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }
  
  
  //with expression:
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, ct_expr<LHS, OP, RHS> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(rhs));
  }
  
  template <typename LHS, typename OP, typename RHS, typename InterfaceType>
  binary_expr<InterfaceType> operator/(ct_expr<LHS, OP, RHS> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new binary_expr<InterfaceType>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with constant:
  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, constant<T> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <typename T, typename InterfaceType>
  binary_expr<InterfaceType> operator/(constant<T> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_constant:
  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, ct_constant<value> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  template <long value, typename InterfaceType>
  binary_expr<InterfaceType> operator/(ct_constant<value> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<long, InterfaceType>(value),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with variable:
  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator/(variable<InterfaceType> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(), new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(), rhs.clone());
  }

  //with ct_variable:
  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, ct_variable<id> const & rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, unsigned long id>
  binary_expr<InterfaceType> operator/(ct_variable<id> const & lhs, binary_expr<InterfaceType> const & rhs)
  {
    //std::cout << "Generating compound: " << lhs << "+" << rhs << std::endl;
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(binary_expr<InterfaceType> const & lhs, default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      constant<typename InterfaceType::numeric_type>(rhs).clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(default_numeric_type lhs, binary_expr<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }


}

#endif