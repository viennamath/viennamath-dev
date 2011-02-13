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
#include "viennamath/binary_operators.hpp"

namespace viennamath
{
  
      
    ////////////////// Operations //////////////////////////////
    
    ////// operator+
    template <typename ScalarType, typename InterfaceType, typename LHS, typename OP, typename RHS>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_plus<typename InterfaceType::numeric_type>,
            ct_expr<LHS, OP, RHS> >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<LHS, OP, RHS> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_plus<typename InterfaceType::numeric_type>,
                     ct_expr<LHS, OP, RHS> >(lhs, other);
    }
    
    // c1 + (c2 + X) -> [c1 + c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<constant<OtherScalarType, InterfaceType>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 + (ct_c2 + X) -> [c1 + ct_c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + value),
                      other.rhs());
    }

    // c1 + (c2 - X) -> [c1 + c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<constant<OtherScalarType, InterfaceType>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 + (ct_c2 - X) -> [c1 + ct_c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + value),
                      other.rhs());
    }

    
    template <typename ScalarType, typename InterfaceType, unsigned long other_id>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_plus<typename InterfaceType::numeric_type>,
            variable<other_id, InterfaceType> >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              variable<other_id, InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_plus<typename InterfaceType::numeric_type>,
                     variable<other_id, InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType>
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              constant<OtherScalarType, InterfaceType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
                      InterfaceType
                     >(lhs.unwrap() + other.unwrap());
    }
    
    template <typename ScalarType, typename InterfaceType, long value>
    constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType>
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type,
                      InterfaceType
                     >(lhs.unwrap() + value);
    }
    
    ////// operator-
    template <typename ScalarType, typename InterfaceType, typename LHS, typename OP, typename RHS>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_minus<typename InterfaceType::numeric_type>,
            ct_expr<LHS, OP, RHS> >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<LHS, OP, RHS> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_minus<typename InterfaceType::numeric_type>,
                     ct_expr<LHS, OP, RHS> >(lhs, other);
    }
    
    // c1 - (c2 + X) -> [c1 - c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<constant<OtherScalarType, InterfaceType>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 - (ct_c2 + X) -> [c1 - ct_c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - value),
                      other.rhs());
    }

    // c1 - (c2 - X) -> [c1 - c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<constant<OtherScalarType, InterfaceType>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 - (ct_c2 - X) -> [c1 - ct_c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - value),
                      other.rhs());
    }

    template <typename ScalarType, typename InterfaceType, unsigned long other_id>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_minus<typename InterfaceType::numeric_type>,
            variable<other_id, InterfaceType> >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              variable<other_id, InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_minus<typename InterfaceType::numeric_type>,
                     variable<other_id, InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
             InterfaceType>
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              constant<OtherScalarType, InterfaceType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
                      InterfaceType
                     >(lhs.unwrap() - other.unwrap());
    }
    
    template <typename ScalarType, typename InterfaceType, long value>
    constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type,
             InterfaceType>
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type,
                      InterfaceType
                     >(lhs.unwrap() - value);
    }




    ////// operator*
    template <typename ScalarType, typename InterfaceType, typename LHS, typename OP, typename RHS>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_mult<typename InterfaceType::numeric_type>,
            ct_expr<LHS, OP, RHS> >
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<LHS, OP, RHS> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_mult<typename InterfaceType::numeric_type>,
                     ct_expr<LHS, OP, RHS> >(lhs, other);
    }
    
    template <typename ScalarType, typename InterfaceType, unsigned long other_id>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_mult<typename InterfaceType::numeric_type>,
            variable<other_id, InterfaceType> >
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              variable<other_id, InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_mult<typename InterfaceType::numeric_type>,
                     variable<other_id, InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_mult<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
             InterfaceType>
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              constant<OtherScalarType, InterfaceType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_mult<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
                      InterfaceType
                     >(lhs.unwrap() * other.unwrap());
    }
    
    template <typename ScalarType, typename InterfaceType, long value>
    constant<typename promote_traits<ScalarType, op_mult<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType>
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_mult<typename InterfaceType::numeric_type>, long>::result_type,
                      InterfaceType
                     >(lhs.unwrap() * value);
    }

    //operator/
    template <typename ScalarType, typename InterfaceType, typename LHS, typename OP, typename RHS>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_div<typename InterfaceType::numeric_type>,
            ct_expr<LHS, OP, RHS> >
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<LHS, OP, RHS> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_div<typename InterfaceType::numeric_type>,
                     ct_expr<LHS, OP, RHS> >(lhs, other);
    }
    
    template <typename ScalarType, typename InterfaceType, unsigned long other_id>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_div<typename InterfaceType::numeric_type>,
            variable<other_id, InterfaceType> >
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              variable<other_id, InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_div<typename InterfaceType::numeric_type>,
                     variable<other_id, InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, typename OtherScalarType>
    constant<typename promote_traits<ScalarType, op_div<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
             InterfaceType>
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              constant<OtherScalarType, InterfaceType> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_div<typename InterfaceType::numeric_type>, OtherScalarType>::result_type,
                      InterfaceType
                     >(lhs.unwrap() / other.unwrap());
    }
    
    template <typename ScalarType, typename InterfaceType, long value>
    constant<typename promote_traits<ScalarType, op_div<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType>
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              ct_constant<value> const & other)
    {
      return constant<typename promote_traits<ScalarType, op_div<typename InterfaceType::numeric_type>, long>::result_type,
                      InterfaceType
                     >(lhs.unwrap() / value);
    }
    

  
  //////////////////// other operators: /////////////////////
  
  template <typename ScalarType, typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream,
                           constant<ScalarType, InterfaceType> const & c)
  {
    stream << c.str();
    return stream;
  }

  
}

#endif