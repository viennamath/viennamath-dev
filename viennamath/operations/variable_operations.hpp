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

#include "viennamath/constant.hpp"
#include "viennamath/vector.hpp"
#include "viennamath/op_tags.hpp"
#include "viennamath/binary_expression.hpp"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/variable.hpp"

#include <assert.h>

namespace viennamath
{

  ////////////////// Operations //////////////////////////////
  
  //operator+
  template <unsigned long id, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id>,
              op_plus,
              ct_expr<LHS, OP, RHS> >
  operator+(variable<id> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id>,
                      op_plus,
                      ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, unsigned long other_id>
  ct_expr<variable<id>,
              op_plus,
              variable<other_id> >
  operator+(variable<id> const & lhs,
            variable<other_id> const & other)
  {
    return ct_expr<variable<id>,
                      op_plus,
                      variable<other_id> >(lhs, other);
  }

  template <unsigned long id>
  ct_expr<ct_constant<2>,
              op_mult,
              variable<id> >
  operator+(variable<id> const & lhs,
            variable<id> const & other)
  {
    return ct_expr<ct_constant<2>,
                      op_mult,
                      variable<id> >(ct_constant<2>(), lhs);
  }

  template <unsigned long id, typename OtherScalarType>
  ct_expr<variable<id>,
              op_plus,
              constant<OtherScalarType> >
  operator+(variable<id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return ct_expr<variable<id>,
                      op_plus,
                      constant<OtherScalarType> >(lhs, other);
  }

  template <unsigned long id, long value>
  ct_expr<variable<id>,
              op_plus,
              ct_constant<value> >
  operator+(variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id>,
                      op_plus,
                      ct_constant<value> >(lhs, other);
  }


  //operator-
  template <unsigned long id, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id>,
              op_minus,
              ct_expr<LHS, OP, RHS> >
  operator-(variable<id> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id>,
                      op_minus,
                      ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, unsigned long other_id>
  ct_expr<variable<id>,
              op_minus,
              variable<other_id> >
  operator-(variable<id> const & lhs,
            variable<other_id> const & other)
  {
    return ct_expr<variable<id>,
                      op_minus,
                      variable<other_id> >(lhs, other);
  }

  template <unsigned long id>
  ct_constant<0>
  operator-(variable<id> const & lhs,
            variable<id> const & other)
  {
    return ct_constant<0>();
  }

  template <unsigned long id, typename OtherScalarType>
  ct_expr<variable<id>,
              op_minus,
              constant<OtherScalarType> >
  operator-(variable<id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return ct_expr<variable<id>,
                      op_minus,
                      constant<OtherScalarType> >(lhs, other);
  }
  
  template <unsigned long id, long value>
  ct_expr<variable<id>,
              op_minus,
              ct_constant<value> >
  operator-(variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id>,
                      op_minus,
                      ct_constant<value> >(lhs, other);
  }


  //operator*
  template <unsigned long id, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id>,
              op_mult,
              ct_expr<LHS, OP, RHS> >
  operator*(variable<id> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id>,
                      op_mult,
                      ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, unsigned long other_id>
  ct_expr<variable<id>,
              op_mult,
              variable<other_id> >
  operator*(variable<id> const & lhs,
            variable<other_id> const & other)
  {
    return ct_expr<variable<id>,
                      op_mult,
                      variable<other_id> >(lhs, other);
  }

  template <unsigned long id, typename OtherScalarType>
  ct_expr<variable<id>,
              op_mult,
              constant<OtherScalarType> >
  operator*(variable<id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return ct_expr<variable<id>,
                      op_mult,
                      constant<OtherScalarType> >(lhs, other);
  }

  template <unsigned long id, long value>
  ct_expr<variable<id>,
              op_mult,
              ct_constant<value> >
  operator*(variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id>,
                      op_mult,
                      ct_constant<value> >(lhs, other);
  }


  //with plain numeric type (see notes on numeric_type_proxy)
  template <unsigned long id>
  binary_expr operator*(variable<id> const & lhs,
                        numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(),
                       op_mult().clone(),
                       constant<numeric_type>(rhs.get()).clone());
  }

  template <unsigned long id>
  binary_expr operator*(numeric_type_proxy lhs,
                        variable<id> const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(),
                       op_mult().clone(),
                       rhs.clone());
  }


  //operator/
  template <unsigned long id, typename LHS, typename OP, typename RHS>
  ct_expr<variable<id>,
              op_div,
              ct_expr<LHS, OP, RHS> >
  operator/(variable<id> const & lhs,
            ct_expr<LHS, OP, RHS> const & other)
  {
    return ct_expr<variable<id>,
                      op_div,
                      ct_expr<LHS, OP, RHS> >(lhs, other);
  }
  
  template <unsigned long id, unsigned long other_id>
  ct_expr<variable<id>,
              op_div,
              variable<other_id> >
  operator/(variable<id> const & lhs,
            variable<other_id> const & other)
  {
    return ct_expr<variable<id>,
                      op_div,
                      variable<other_id> >(lhs, other);
  }

  template <unsigned long id>
  ct_constant<1>
  operator/(variable<id> const & lhs,
            variable<id> const & other)
  {
    return ct_constant<1>();
  }

  template <unsigned long id, typename OtherScalarType>
  ct_expr<variable<id>,
              op_div,
              constant<OtherScalarType> >
  operator/(variable<id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return ct_expr<variable<id>,
                      op_div,
                      constant<OtherScalarType> >(lhs, other);
  }
  
  template <unsigned long id, long value>
  ct_expr<variable<id>,
              op_div,
              ct_constant<value> >
  operator/(variable<id> const & lhs,
            ct_constant<value> const & other)
  {
    return ct_expr<variable<id>,
                      op_div,
                      ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <unsigned long id>
  binary_expr operator/(variable<id> const & lhs,
                 numeric_type_proxy rhs)
  {
    return binary_expr(lhs.clone(),
                op_div().clone(),
                constant<numeric_type>(rhs.get()).clone());
  }

  template <unsigned long id>
  binary_expr operator/(numeric_type_proxy lhs,
                 variable<id> const & rhs)
  {
    return binary_expr(constant<numeric_type>(lhs.get()).clone(),
                op_div().clone(),
                rhs.clone());
  }

}

#endif