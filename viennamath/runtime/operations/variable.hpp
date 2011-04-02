/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_VARIABLE_OPERATION_CPP
#define VIENNAMATH_VARIABLE_OPERATION_CPP

#include "viennamath/runtime/constant.hpp"
#include "viennamath/compiletime/ct_vector.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/compiletime/ct_expr.hpp"
#include "viennamath/runtime/variable.hpp"

#include <assert.h>

namespace viennamath
{

  ////////////////// Operations //////////////////////////////
  
  ////////////// operator+
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> 
  operator+(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(other));
  }
  
  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator+(variable<InterfaceType> const & lhs,
            ct_variable<id> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator+(ct_variable<id>const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> 
  operator+(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, typename OtherScalarType>
  binary_expr<InterfaceType> 
  operator+(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> 
  operator+(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType>
  operator+(variable<InterfaceType> const & lhs,
            default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(default_numeric_type lhs,
                                       variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }




  ////////// operator-
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> 
  operator-(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(other));
  }
  
  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator-(variable<InterfaceType> const & lhs,
            ct_variable<id> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator-(ct_variable<id>const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> 
  operator-(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, typename OtherScalarType>
  binary_expr<InterfaceType> 
  operator-(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> 
  operator-(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(variable<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator-(default_numeric_type lhs,
                                       variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }






  ////////////// operator*
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> 
  operator*(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(other));
  }
  
  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator*(variable<InterfaceType> const & lhs,
            ct_variable<id> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator*(ct_variable<id>const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> 
  operator*(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, typename OtherScalarType>
  binary_expr<InterfaceType> 
  operator*(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> 
  operator*(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }


  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(variable<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs));
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator*(default_numeric_type lhs,
                                       variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }







  //////////// operator/
  template <typename InterfaceType, typename LHS, typename OP, typename RHS>
  binary_expr<InterfaceType> 
  operator/(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new binary_expr<InterfaceType>(other));
  }
  
  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator/(variable<InterfaceType> const & lhs,
            ct_variable<id> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new variable<InterfaceType>(id));
  }

  template <typename InterfaceType, id_type id>
  binary_expr<InterfaceType> 
  operator/(ct_variable<id>const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> 
  operator/(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, typename OtherScalarType>
  binary_expr<InterfaceType> 
  operator/(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      other.clone());
  }

  template <typename InterfaceType, long value>
  binary_expr<InterfaceType> 
  operator/(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<long, InterfaceType>(value));
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(variable<InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <typename InterfaceType>
  binary_expr<InterfaceType> operator/(default_numeric_type lhs,
                                       variable<InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

}

#endif