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
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  
      
    ////////////////// Operations //////////////////////////////
    
    //operator+
    template <typename ScalarType, typename LHS, typename OP, typename RHS>
    expression<constant<ScalarType>,
               op_plus,
               expression<LHS, OP, RHS> >
    operator+(constant<ScalarType> const & lhs, expression<LHS, OP, RHS> const & other)
    {
      return expression<constant<ScalarType>,
                        op_plus,
                        expression<LHS, OP, RHS> >(lhs, other);
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
    expression<constant<ScalarType>,
               op_plus,
               constant<OtherScalarType> >
    operator+(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return expression<constant<ScalarType>,
                        op_plus,
                        constant<OtherScalarType> >(lhs, other);
    }

    template <typename ScalarType, long value>
    expression<constant<ScalarType>,
               op_plus,
               ct_constant<value> >
    operator+(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return expression<constant<ScalarType>,
                        op_plus,
                        ct_constant<value> >(lhs, other);
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
    expression<constant<ScalarType>,
               op_minus,
               constant<OtherScalarType> >
    operator-(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return expression<constant<ScalarType>,
                        op_minus,
                        constant<OtherScalarType> >(lhs, other);
    }
    
    template <typename ScalarType, long value>
    expression<constant<ScalarType>,
               op_minus,
               ct_constant<value> >
    operator-(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return expression<constant<ScalarType>,
                        op_minus,
                        ct_constant<value> >(lhs, other);
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
    expression<constant<ScalarType>,
               op_mult,
               constant<OtherScalarType> >
    operator*(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return expression<constant<ScalarType>,
                        op_mult,
                        constant<OtherScalarType> >(lhs, other);
    }

    template <typename ScalarType, long value>
    expression<constant<ScalarType>,
               op_mult,
               ct_constant<value> >
    operator*(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return expression<constant<ScalarType>,
                        op_mult,
                        ct_constant<value> >(lhs, other);
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
    expression<constant<ScalarType>,
               op_div,
               constant<OtherScalarType> >
    operator/(constant<ScalarType> const & lhs, constant<OtherScalarType> const & other)
    {
      return expression<constant<ScalarType>,
                        op_div,
                        constant<OtherScalarType> >(lhs, other);
    }
    
    template <typename ScalarType, long value>
    expression<constant<ScalarType>,
               op_div,
               ct_constant<value> >
    operator/(constant<ScalarType> const & lhs, ct_constant<value> const & other)
    {
      return expression<constant<ScalarType>,
                        op_div,
                        ct_constant<value> >(lhs, other);
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