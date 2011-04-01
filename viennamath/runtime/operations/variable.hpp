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
  ct_expr<variable<InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator+(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename InterfaceType>
  ct_expr<variable<InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          variable<InterfaceType> >
  operator+(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   variable<InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType>
  ct_expr<ct_constant<2>,
          op_mult<typename InterfaceType::numeric_type>,
          variable<InterfaceType> >
  operator+(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_expr<ct_constant<2>,
                   op_mult<typename InterfaceType::numeric_type>,
                   variable<InterfaceType> >(ct_constant<2>(), lhs);
  }

  template <typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator+(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType, long value>
  ct_expr<variable<InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator+(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <typename InterfaceType>
  binary_expr<InterfaceType> operator+(variable<InterfaceType> const & lhs,
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
  ct_expr<variable<InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator-(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename InterfaceType>
  ct_expr<variable<InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          variable<InterfaceType> >
  operator-(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   variable<InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType>
  ct_constant<0>
  operator-(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_constant<0>();
  }

  template <typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator-(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }
  
  template <typename InterfaceType, long value>
  ct_expr<variable<InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator-(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
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
  ct_expr<variable<InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator*(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename InterfaceType>
  ct_expr<variable<InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          variable<InterfaceType> >
  operator*(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   variable<InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator*(variable<InterfaceType> const & lhs,
           constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType, long value>
  ct_expr<variable<InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator*(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
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
  ct_expr<variable<InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator/(variable<InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename InterfaceType>
  ct_expr<variable<InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          variable<InterfaceType> >
  operator/(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   variable<InterfaceType> >(lhs, other);
  }

  template <typename InterfaceType>
  ct_constant<1>
  operator/(variable<InterfaceType> const & lhs,
            variable<InterfaceType> const & other)
  {
    return ct_constant<1>();
  }

  template <typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator/(variable<InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }
  
  template <typename InterfaceType, long value>
  ct_expr<variable<InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator/(variable<InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
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