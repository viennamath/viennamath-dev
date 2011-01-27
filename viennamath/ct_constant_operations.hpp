/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_CONSTANT_OPERATIONS_HPP
#define VIENNAMATH_CT_CONSTANT_OPERATIONS_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/binary_expression.hpp"
#include "viennamath/op_tags.hpp"
#include "viennamath/ct_constant.hpp"

namespace viennamath
{
  
      
  ////////////////// Operations //////////////////////////////
  
  //operator+
  template <long value, typename LHS, typename OP, typename RHS>
  expression<ct_constant<value>,
            op_plus,
            expression<LHS, OP, RHS> >
  operator+(ct_constant<value> const & lhs, 
            expression<LHS, OP, RHS> const & other)
  {
    return expression<ct_constant<value>,
                      op_plus,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  // ct_c1 + (c2 + X) -> [ct_c1 + c2] + X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  expression<constant< typename promote_traits<long, op_plus, ScalarType>::result_type >,
              op_plus,
              RHS >
  operator+(ct_constant<value> const & lhs, 
            expression<constant<ScalarType>, op_plus, RHS> const & other)
  {
    typedef constant< typename promote_traits<long, op_plus, ScalarType>::result_type >   result_constant;
    return expression<result_constant,
                      op_plus,
                      RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 + X) -> [ct_c1 + ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  expression<ct_constant<value + value2>,
            op_plus,
            RHS >
  operator+(ct_constant<value> const & lhs, 
            expression<ct_constant<value2>, op_plus, RHS> const & other)
  {
    return expression<ct_constant<value + value2>,
                      op_plus,
                      RHS >(ct_constant<value + value2>(), other.rhs());
  }
  
  // ct_c1 + (c2 - X)    -> [ct_c1 + c2]    - X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  expression<constant< typename promote_traits<long, op_plus, ScalarType>::result_type >,
              op_minus,
              RHS >
  operator+(ct_constant<value> const & lhs, 
            expression<constant<ScalarType>, op_minus, RHS> const & other)
  {
    typedef constant< typename promote_traits<long, op_plus, ScalarType>::result_type >   result_constant;
    return expression<result_constant,
                      op_minus,
                      RHS >(result_constant(value + other.lhs()), other.rhs());
  }
  
  // ct_c1 + (ct_c2 - X) -> [ct_c1 + ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  expression<ct_constant<value + value2>,
            op_minus,
            RHS >
  operator+(ct_constant<value> const & lhs, 
            expression<ct_constant<value2>, op_minus, RHS> const & other)
  {
    return expression<ct_constant<value + value2>,
                      op_minus,
                      RHS >(ct_constant<value + value2>(), other.rhs());
  }
  
  template <long value, unsigned long other_id>
  expression<ct_constant<value>,
            op_plus,
            variable<other_id> >
  operator+(ct_constant<value> const & lhs, 
            variable<other_id> const & other)
  {
    return expression<ct_constant<value>,
                      op_plus,
                      variable<other_id> >(lhs, other);
  }

  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator+(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value + other());
  }

  template <long value, long other_value>
  ct_constant<value + other_value>
  operator+(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value + other_value>();
  }


  //operator-
  template <long value, typename LHS, typename OP, typename RHS>
  expression<ct_constant<value>,
            op_minus,
            expression<LHS, OP, RHS> >
  operator-(ct_constant<value> const & lhs, 
            expression<LHS, OP, RHS> const & other)
  {
    return expression<ct_constant<value>,
                      op_minus,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  // ct_c1 - (c2 + X) -> [ct_c1 - c2] - X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  expression<constant< typename promote_traits<long, op_minus, ScalarType>::result_type >,
              op_minus,
              RHS >
  operator-(ct_constant<value> const & lhs, 
            expression<constant<ScalarType>, op_plus, RHS> const & other)
  {
    typedef constant< typename promote_traits<long, op_minus, ScalarType>::result_type >   result_constant;
    return expression<result_constant,
                      op_minus,
                      RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 + X) -> [ct_c1 - ct_c2] - X, where X is anything:
  template <long value, long value2, typename RHS>
  expression<ct_constant<value - value2>,
            op_minus,
            RHS >
  operator-(ct_constant<value> const & lhs, 
            expression<ct_constant<value2>, op_plus, RHS> const & other)
  {
    return expression<ct_constant<value - value2>,
                      op_minus,
                      RHS >(ct_constant<value - value2>(), other.rhs());
  }
  
  // ct_c1 - (c2 - X)    -> [ct_c1 - c2] + X, where X is anything:
  template <long value, typename ScalarType, typename RHS>
  expression<constant< typename promote_traits<long, op_minus, ScalarType>::result_type >,
              op_plus,
              RHS >
  operator-(ct_constant<value> const & lhs, 
            expression<constant<ScalarType>, op_minus, RHS> const & other)
  {
    typedef constant< typename promote_traits<long, op_minus, ScalarType>::result_type >   result_constant;
    return expression<result_constant,
                      op_plus,
                      RHS >(result_constant(value - other.lhs()), other.rhs());
  }
  
  // ct_c1 - (ct_c2 - X) -> [ct_c1 - ct_c2] + X, where X is anything:
  template <long value, long value2, typename RHS>
  expression<ct_constant<value - value2>,
            op_plus,
            RHS >
  operator-(ct_constant<value> const & lhs, 
            expression<ct_constant<value2>, op_minus, RHS> const & other)
  {
    return expression<ct_constant<value - value2>,
                      op_plus,
                      RHS >(ct_constant<value - value2>(), other.rhs());
  }
  
  
  template <long value, unsigned long other_id>
  expression<ct_constant<value>,
            op_minus,
            variable<other_id> >
  operator-(ct_constant<value> const & lhs, 
            variable<other_id> const & other)
  {
    return expression<ct_constant<value>,
                      op_minus,
                      variable<other_id> >(lhs, other);
  }

  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator-(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value - other());
  }
  
  template <long value, long other_value>
  ct_constant<value - other_value>
  operator-(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value - other_value>();
  }


  //operator*
  template <long value, typename LHS, typename OP, typename RHS>
  expression<ct_constant<value>,
            op_mult,
            expression<LHS, OP, RHS> >
  operator*(ct_constant<value> const & lhs, 
            expression<LHS, OP, RHS> const & other)
  {
    return expression<ct_constant<value>,
                      op_mult,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <long value, unsigned long other_id>
  expression<ct_constant<value>,
            op_mult,
            variable<other_id> >
  operator*(ct_constant<value> const & lhs, 
            variable<other_id> const & other)
  {
    return expression<ct_constant<value>,
                      op_mult,
                      variable<other_id> >(lhs, other);
  }

  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator*(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value * other());
  }

  template <long value, long other_value>
  ct_constant<value * other_value>
  operator*(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return ct_constant<value * other_value>();
  }


  //operator/
  template <long value, typename LHS, typename OP, typename RHS>
  expression<ct_constant<value>,
            op_div,
            expression<LHS, OP, RHS> >
  operator/(ct_constant<value> const & lhs, 
            expression<LHS, OP, RHS> const & other)
  {
    return expression<ct_constant<value>,
                      op_div,
                      expression<LHS, OP, RHS> >(lhs, other);
  }
  
  template <long value, unsigned long other_id>
  expression<ct_constant<value>,
            op_div,
            variable<other_id> >
  operator/(ct_constant<value> const & lhs, 
            variable<other_id> const & other)
  {
    return expression<ct_constant<value>,
                      op_div,
                      variable<other_id> >(lhs, other);
  }

  template <long value, typename OtherScalarType>
  constant<typename promote_traits<long, op_div, OtherScalarType>::result_type>           
  operator/(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    typedef typename promote_traits<long, op_div, OtherScalarType>::result_type  result_type;
    
    return constant<result_type>(static_cast<result_type>(value) / static_cast<result_type>(other()));
  }
  
  template <long value, long other_value>
  expression<ct_constant<value>,
            op_div,
            ct_constant<other_value> >
  operator/(ct_constant<value> const & lhs, 
            ct_constant<other_value> const & other)
  {
    return expression<ct_constant<value>,
                      op_div,
                      ct_constant<other_value> >(lhs, other);
  }


  
  
}

#endif