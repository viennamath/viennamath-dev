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
  template <unsigned long id, typename InterfaceType, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id, InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator+(variable<id, InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, unsigned long other_id>
  ct_expr<variable<id, InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          variable<other_id, InterfaceType> >
  operator+(variable<id, InterfaceType> const & lhs,
            variable<other_id, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   variable<other_id, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType>
  ct_expr<ct_constant<2>,
          op_mult<typename InterfaceType::numeric_type>,
          variable<id, InterfaceType> >
  operator+(variable<id, InterfaceType> const & lhs,
            variable<id, InterfaceType> const & other)
  {
    return ct_expr<ct_constant<2>,
                   op_mult<typename InterfaceType::numeric_type>,
                   variable<id, InterfaceType> >(ct_constant<2>(), lhs);
  }

  template <unsigned long id, typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<id, InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator+(variable<id, InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType, long value>
  ct_expr<variable<id, InterfaceType>,
          op_plus<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator+(variable<id, InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_plus<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator+(variable<id, InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator+(default_numeric_type lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }




  ////////// operator-
  template <unsigned long id, typename InterfaceType, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id, InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator-(variable<id, InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, unsigned long other_id>
  ct_expr<variable<id, InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          variable<other_id, InterfaceType> >
  operator-(variable<id, InterfaceType> const & lhs,
            variable<other_id, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   variable<other_id, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType>
  ct_constant<0>
  operator-(variable<id, InterfaceType> const & lhs,
            variable<id, InterfaceType> const & other)
  {
    return ct_constant<0>();
  }

  template <unsigned long id, typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<id, InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator-(variable<id, InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, long value>
  ct_expr<variable<id, InterfaceType>,
          op_minus<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator-(variable<id, InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_minus<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator-(variable<id, InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator-(default_numeric_type lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }






  ////////////// operator*
  template <unsigned long id, typename InterfaceType, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id, InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator*(variable<id, InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, unsigned long other_id>
  ct_expr<variable<id, InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          variable<other_id, InterfaceType> >
  operator*(variable<id, InterfaceType> const & lhs,
            variable<other_id, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   variable<other_id, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<id, InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator*(variable<id, InterfaceType> const & lhs,
           constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType, long value>
  ct_expr<variable<id, InterfaceType>,
          op_mult<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator*(variable<id, InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_mult<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
  }


  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator*(variable<id, InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs));
  }

  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator*(default_numeric_type lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }







  //////////// operator/
  template <unsigned long id, typename InterfaceType, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id, InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          ct_expr<LHS, OP, RHS> >
  operator/(variable<id, InterfaceType> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, unsigned long other_id>
  ct_expr<variable<id, InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          variable<other_id, InterfaceType> >
  operator/(variable<id, InterfaceType> const & lhs,
            variable<other_id, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   variable<other_id, InterfaceType> >(lhs, other);
  }

  template <unsigned long id, typename InterfaceType>
  ct_constant<1>
  operator/(variable<id, InterfaceType> const & lhs,
            variable<id, InterfaceType> const & other)
  {
    return ct_constant<1>();
  }

  template <unsigned long id, typename InterfaceType, typename OtherScalarType>
  ct_expr<variable<id, InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          constant<OtherScalarType, InterfaceType> >
  operator/(variable<id, InterfaceType> const & lhs,
            constant<OtherScalarType, InterfaceType> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   constant<OtherScalarType, InterfaceType> >(lhs, other);
  }
  
  template <unsigned long id, typename InterfaceType, long value>
  ct_expr<variable<id, InterfaceType>,
          op_div<typename InterfaceType::numeric_type>,
          ct_constant<value> >
  operator/(variable<id, InterfaceType> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id, InterfaceType>,
                   op_div<typename InterfaceType::numeric_type>,
                   ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy<NumericT>)
  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator/(variable<id, InterfaceType> const & lhs,
                                       default_numeric_type rhs)
  {
    return binary_expr<InterfaceType>(lhs.clone(),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      new constant<typename InterfaceType::numeric_type, InterfaceType>(rhs)
                                     );
  }

  template <unsigned long id, typename InterfaceType>
  binary_expr<InterfaceType> operator/(default_numeric_type lhs,
                                       variable<id, InterfaceType> const & rhs)
  {
    return binary_expr<InterfaceType>(new constant<typename InterfaceType::numeric_type, InterfaceType>(lhs),
                                      new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                      rhs.clone());
  }

}

#endif