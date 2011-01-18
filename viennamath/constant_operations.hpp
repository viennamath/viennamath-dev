/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CONSTANT_OPERATIONS_HPP
#define VIENNAMATH_CONSTANT_OPERATIONS_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/promote_traits.hpp"
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  
      
    ////////////////// Operations //////////////////////////////
    
    //operator+
    template <typename ScalarType, typename LHS, typename OP, typename RHS>
    expression<constant<ScalarType>,
               op_plus,
               expression<LHS, OP, RHS> >
    operator+(constant<ScalarType> const & lhs,
              expression<LHS, OP, RHS> const & other)
    {
      return expression<constant<ScalarType>,
                        op_plus,
                        expression<LHS, OP, RHS> >(lhs, other);
    }
    
    // c1 + (c2 + X) -> [c1 + c2] + X, where X is anything:
    template <typename ScalarType, typename OtherScalarType, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type >,
               op_plus,
               RHS >
    operator+(constant<ScalarType> const & lhs,
              expression<constant<OtherScalarType>, op_plus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_plus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                         other.rhs());
    }

    // c1 + (ct_c2 + X) -> [c1 + ct_c2] + X, where X is anything:
    template <typename ScalarType, long value, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_plus, long>::result_type >,
               op_plus,
               RHS >
    operator+(constant<ScalarType> const & lhs,
              expression<ct_constant<value>, op_plus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus, long>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_plus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) + value),
                         other.rhs());
    }

    // c1 + (c2 - X) -> [c1 + c2] - X, where X is anything:
    template <typename ScalarType, typename OtherScalarType, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type >,
               op_minus,
               RHS >
    operator+(constant<ScalarType> const & lhs,
              expression<constant<OtherScalarType>, op_minus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_minus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                         other.rhs());
    }

    // c1 + (ct_c2 - X) -> [c1 + ct_c2] - X, where X is anything:
    template <typename ScalarType, long value, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_plus, long>::result_type >,
               op_minus,
               RHS >
    operator+(constant<ScalarType> const & lhs,
              expression<ct_constant<value>, op_minus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus, long>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_minus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) + value),
                         other.rhs());
    }

    
    template <typename ScalarType, typename OtherScalarType, unsigned long other_id>
    expression<constant<ScalarType>,
               op_plus,
               unknown<OtherScalarType, other_id> >
    operator+(constant<ScalarType> const & lhs, unknown<OtherScalarType, other_id> const & other)
    {
      return expression<constant<ScalarType>,
                        op_plus,
                        unknown<OtherScalarType, other_id> >(lhs, other);
    }

    template <typename ScalarType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type>
    operator+(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_plus, OtherScalarType>::result_type
                     >(lhs.unwrap() + other.unwrap());
    }
    
    template <typename ScalarType, long value>
    constant<typename promote_traits<ScalarType, op_plus, long>::result_type>
    operator+(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_plus, long>::result_type
                     >(lhs.unwrap() + value);
    }
    
    //operator-
    template <typename ScalarType, typename LHS, typename OP, typename RHS>
    expression<constant<ScalarType>,
               op_minus,
               expression<LHS, OP, RHS> >
    operator-(constant<ScalarType> const & lhs, expression<LHS, OP, RHS> const & other)
    {
      return expression<constant<ScalarType>,
                        op_minus,
                        expression<LHS, OP, RHS> >(lhs, other);
    }
    
    // c1 - (c2 + X) -> [c1 - c2] - X, where X is anything:
    template <typename ScalarType, typename OtherScalarType, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type >,
               op_minus,
               RHS >
    operator-(constant<ScalarType> const & lhs,
              expression<constant<OtherScalarType>, op_plus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_minus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                         other.rhs());
    }

    // c1 - (ct_c2 + X) -> [c1 - ct_c2] - X, where X is anything:
    template <typename ScalarType, long value, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_minus, long>::result_type >,
               op_minus,
               RHS >
    operator-(constant<ScalarType> const & lhs,
              expression<ct_constant<value>, op_plus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus, long>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_minus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) - value),
                         other.rhs());
    }

    // c1 - (c2 - X) -> [c1 - c2] + X, where X is anything:
    template <typename ScalarType, typename OtherScalarType, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type >,
               op_plus,
               RHS >
    operator-(constant<ScalarType> const & lhs,
              expression<constant<OtherScalarType>, op_minus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_plus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                         other.rhs());
    }

    // c1 - (ct_c2 - X) -> [c1 - ct_c2] + X, where X is anything:
    template <typename ScalarType, long value, typename RHS>
    expression<constant<typename promote_traits<ScalarType, op_minus, long>::result_type >,
               op_plus,
               RHS >
    operator-(constant<ScalarType> const & lhs,
              expression<ct_constant<value>, op_minus, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus, long>::result_type >  ret_constant;
      return expression<ret_constant,
                        op_plus,
                        RHS
                       >(ret_constant(static_cast<ScalarType>(lhs) - value),
                         other.rhs());
    }

    template <typename ScalarType, typename OtherScalarType, unsigned long other_id>
    expression<constant<ScalarType>,
               op_minus,
               unknown<OtherScalarType, other_id> >
    operator-(constant<ScalarType> const & lhs, unknown<OtherScalarType, other_id> const & other)
    {
      return expression<constant<ScalarType>,
                        op_minus,
                        unknown<OtherScalarType, other_id> >(lhs, other);
    }

    template <typename ScalarType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type>
    operator-(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_minus, OtherScalarType>::result_type
                     >(lhs.unwrap() - other.unwrap());
    }
    
    template <typename ScalarType, long value>
    constant<typename promote_traits<ScalarType, op_minus, long>::result_type>
    operator-(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_minus, long>::result_type
                     >(lhs.unwrap() - value);
    }

    //operator*
    template <typename ScalarType, typename LHS, typename OP, typename RHS>
    expression<constant<ScalarType>,
               op_mult,
               expression<LHS, OP, RHS> >
    operator*(constant<ScalarType> const & lhs, expression<LHS, OP, RHS> const & other)
    {
      return expression<constant<ScalarType>,
                        op_mult,
                        expression<LHS, OP, RHS> >(lhs, other);
    }
    
    template <typename ScalarType, typename OtherScalarType, unsigned long other_id>
    expression<constant<ScalarType>,
               op_mult,
               unknown<OtherScalarType, other_id> >
    operator*(constant<ScalarType> const & lhs, unknown<OtherScalarType, other_id> const & other)
    {
      return expression<constant<ScalarType>,
                        op_mult,
                        unknown<OtherScalarType, other_id> >(lhs, other);
    }

    template <typename ScalarType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_mult, OtherScalarType>::result_type>
    operator*(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_mult, OtherScalarType>::result_type
                     >(lhs.unwrap() * other.unwrap());
    }
    
    template <typename ScalarType, long value>
    constant<typename promote_traits<ScalarType, op_mult, long>::result_type>
    operator*(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_mult, long>::result_type
                     >(lhs.unwrap() * value);
    }

    //operator/
    template <typename ScalarType, typename LHS, typename OP, typename RHS>
    expression<constant<ScalarType>,
               op_div,
               expression<LHS, OP, RHS> >
    operator/(constant<ScalarType> const & lhs, expression<LHS, OP, RHS> const & other)
    {
      return expression<constant<ScalarType>,
                        op_div,
                        expression<LHS, OP, RHS> >(lhs, other);
    }
    
    template <typename ScalarType, typename OtherScalarType, unsigned long other_id>
    expression<constant<ScalarType>,
               op_div,
               unknown<OtherScalarType, other_id> >
    operator/(constant<ScalarType> const & lhs, unknown<OtherScalarType, other_id> const & other)
    {
      return expression<constant<ScalarType>,
                        op_div,
                        unknown<OtherScalarType, other_id> >(lhs, other);
    }

    template <typename ScalarType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_div, OtherScalarType>::result_type>
    operator/(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_div, OtherScalarType>::result_type
                     >(lhs.unwrap() / other.unwrap());
    }
    
    template <typename ScalarType, long value>
    constant<typename promote_traits<ScalarType, op_div, long>::result_type>
    operator/(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_div, long>::result_type
                     >(lhs.unwrap() / value);
    }
    

  
  //////////////////// other operators: /////////////////////
  
  template <typename ScalarType>
  std::ostream& operator<<(std::ostream & stream, constant<ScalarType> const & c)
  {
    stream << c.str();
    return stream;
  }

  
}

#endif