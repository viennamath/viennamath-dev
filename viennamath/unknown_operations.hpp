/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNKNOWN_OPERATION_CPP
#define VIENNAMATH_UNKNOWN_OPERATION_CPP

#include "viennamath/constant.hpp"
#include "viennamath/vector.hpp"
#include "viennamath/op_tags.hpp"
#include "viennamath/expression_run_time.hpp"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/unknown.hpp"

#include <assert.h>

namespace viennamath
{

  ////////////////// Operations //////////////////////////////
  
  //operator+
  template <typename ScalarType, unsigned long id, typename LHS, typename OP, typename RHS>
  expression<unknown<ScalarType, id>,
              op_plus,
              expression<LHS, OP, RHS> >
  operator+(unknown<ScalarType, id> const & lhs,
            expression<LHS, OP, RHS> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_plus,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, typename OtherScalarType, unsigned long other_id>
  expression<unknown<ScalarType, id>,
              op_plus,
              unknown<OtherScalarType, other_id> >
  operator+(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, other_id> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_plus,
                      unknown<OtherScalarType, other_id> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id>
  expression<ct_constant<2>,
              op_mult,
              unknown<ScalarType, id> >
  operator+(unknown<ScalarType, id> const & lhs,
            unknown<ScalarType, id> const & other)
  {
    return expression<ct_constant<2>,
                      op_mult,
                      unknown<ScalarType, id> >(ct_constant<2>(), lhs);
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  expression<unknown<ScalarType, id>,
              op_plus,
              constant<OtherScalarType> >
  operator+(unknown<ScalarType, id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_plus,
                      constant<OtherScalarType> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id, long value>
  expression<unknown<ScalarType, id>,
              op_plus,
              ct_constant<value> >
  operator+(unknown<ScalarType, id> const & lhs,
            ct_constant<value> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_plus,
                      ct_constant<value> >(lhs, other);
  }


  //operator-
  template <typename ScalarType, unsigned long id, typename LHS, typename OP, typename RHS>
  expression<unknown<ScalarType, id>,
              op_minus,
              expression<LHS, OP, RHS> >
  operator-(unknown<ScalarType, id> const & lhs,
            expression<LHS, OP, RHS> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_minus,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, typename OtherScalarType, unsigned long other_id>
  expression<unknown<ScalarType, id>,
              op_minus,
              unknown<OtherScalarType, other_id> >
  operator-(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, other_id> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_minus,
                      unknown<OtherScalarType, other_id> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  ct_constant<0>
  operator-(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, id> const & other)
  {
    return ct_constant<0>();
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  expression<unknown<ScalarType, id>,
              op_minus,
              constant<OtherScalarType> >
  operator-(unknown<ScalarType, id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_minus,
                      constant<OtherScalarType> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, long value>
  expression<unknown<ScalarType, id>,
              op_minus,
              ct_constant<value> >
  operator-(unknown<ScalarType, id> const & lhs,
            ct_constant<value> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_minus,
                      ct_constant<value> >(lhs, other);
  }


  //operator*
  template <typename ScalarType, unsigned long id, typename LHS, typename OP, typename RHS>
  expression<unknown<ScalarType, id>,
              op_mult,
              expression<LHS, OP, RHS> >
  operator*(unknown<ScalarType, id> const & lhs,
            expression<LHS, OP, RHS> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_mult,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, typename OtherScalarType, unsigned long other_id>
  expression<unknown<ScalarType, id>,
              op_mult,
              unknown<OtherScalarType, other_id> >
  operator*(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, other_id> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_mult,
                      unknown<OtherScalarType, other_id> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  expression<unknown<ScalarType, id>,
              op_mult,
              constant<OtherScalarType> >
  operator*(unknown<ScalarType, id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_mult,
                      constant<OtherScalarType> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id, long value>
  expression<unknown<ScalarType, id>,
              op_mult,
              ct_constant<value> >
  operator*(unknown<ScalarType, id> const & lhs,
            ct_constant<value> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_mult,
                      ct_constant<value> >(lhs, other);
  }


  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename ScalarType, unsigned long id>
  expr operator*(unknown<ScalarType, id> const & lhs,
                 numeric_type_proxy rhs)
  {
    return expr(lhs.clone(),
                op_mult().clone(),
                constant<numeric_type>(rhs.get()).clone());
  }

  template <typename ScalarType, unsigned long id>
  expr operator*(numeric_type_proxy lhs,
                 unknown<ScalarType, id> const & rhs)
  {
    return expr(constant<numeric_type>(lhs.get()).clone(),
                op_mult().clone(),
                rhs.clone());
  }


  //operator/
  template <typename ScalarType, unsigned long id, typename LHS, typename OP, typename RHS>
  expression<unknown<ScalarType, id>,
              op_div,
              expression<LHS, OP, RHS> >
  operator/(unknown<ScalarType, id> const & lhs,
            expression<LHS, OP, RHS> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_div,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, typename OtherScalarType, unsigned long other_id>
  expression<unknown<ScalarType, id>,
              op_div,
              unknown<OtherScalarType, other_id> >
  operator/(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, other_id> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_div,
                      unknown<OtherScalarType, other_id> >(lhs, other);
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  ct_constant<1>
  operator/(unknown<ScalarType, id> const & lhs,
            unknown<OtherScalarType, id> const & other)
  {
    return ct_constant<1>();
  }

  template <typename ScalarType, unsigned long id, typename OtherScalarType>
  expression<unknown<ScalarType, id>,
              op_div,
              constant<OtherScalarType> >
  operator/(unknown<ScalarType, id> const & lhs,
            constant<OtherScalarType> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_div,
                      constant<OtherScalarType> >(lhs, other);
  }
  
  template <typename ScalarType, unsigned long id, long value>
  expression<unknown<ScalarType, id>,
              op_div,
              ct_constant<value> >
  operator/(unknown<ScalarType, id> const & lhs,
            ct_constant<value> const & other)
  {
    return expression<unknown<ScalarType, id>,
                      op_div,
                      ct_constant<value> >(lhs, other);
  }

  //with plain numeric type (see notes on numeric_type_proxy)
  template <typename ScalarType, unsigned long id>
  expr operator/(unknown<ScalarType, id> const & lhs,
                 numeric_type_proxy rhs)
  {
    return expr(lhs.clone(),
                op_div().clone(),
                constant<numeric_type>(rhs.get()).clone());
  }

  template <typename ScalarType, unsigned long id>
  expr operator/(numeric_type_proxy lhs,
                 unknown<ScalarType, id> const & rhs)
  {
    return expr(constant<numeric_type>(lhs.get()).clone(),
                op_div().clone(),
                rhs.clone());
  }

}

#endif