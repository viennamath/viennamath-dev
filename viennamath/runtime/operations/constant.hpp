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
#include "viennamath/compiletime/promote_traits.hpp"
#include "viennamath/runtime/binary_operators.hpp"

namespace viennamath
{
  
    //some misc stuff from compile time types:
  
      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_plus<default_numeric_type>,
              constant<ScalarType, InterfaceType> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_plus<default_numeric_type>,
                       constant<ScalarType, InterfaceType> >(lhs, other);
      }

      // (c1 + X) + c2 -> [c1 + c2] + X
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename T, typename InterfaceType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus<T>, ScalarType>::result_type >,
               op_plus<T>,
               RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_plus<T>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus<T>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_plus<T>,
                       RHS >(lhs.lhs() + other,
                             lhs.rhs());
      }

      // (ct_c1 + X) + c2 -> [ct_c1 + c2] + X
      template <long value, typename RHS, typename ScalarType, typename T, typename InterfaceType>
      ct_expr< constant<typename promote_traits<long, op_plus<T>, ScalarType>::result_type >,
               op_plus<T>,
               RHS >
      operator+(ct_expr<ct_constant<value>, op_plus<T>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<long, op_plus<T>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_plus<T>,
                       RHS >(result_constant(value + other),
                             lhs.rhs());
      }


      // (c1 - X) + c2 -> [c1 + c2] - X
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr< constant<default_numeric_type, InterfaceType>,
               op_minus<default_numeric_type>,
               RHS >
      operator+(ct_expr<constant<OtherScalarType, InterfaceType>, op_minus<default_numeric_type>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant<default_numeric_type, InterfaceType>    result_constant;
        
        return ct_expr<result_constant,
                       op_minus<default_numeric_type>,
                       RHS >(result_constant(lhs.lhs().unwrap() + other.unwrap()),
                             lhs.rhs());
      }

      // (ct_c1 - X) + c2 -> [ct_c1 + c2] - X
      template <long value, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr< constant<default_numeric_type, InterfaceType >,
               op_minus<default_numeric_type>,
               RHS >
      operator+(ct_expr<ct_constant<value>, op_minus<default_numeric_type>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant<ScalarType, InterfaceType>    result_constant;
        return ct_expr<result_constant,
                       op_minus<default_numeric_type>,
                       RHS >(result_constant(value + other),
                             lhs.rhs());
      }
  
  
      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_minus< default_numeric_type >,
              constant<ScalarType, InterfaceType> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_minus< default_numeric_type >,
                       constant<ScalarType, InterfaceType> >(lhs, other);
      }
      
      // (c1 + X) - c2 -> [c1 - c2] + X
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename T, typename InterfaceType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_minus<ScalarType>, ScalarType>::result_type >,
               op_plus<T>,
               RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_plus<T>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_minus<ScalarType>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_plus<T>,
                       RHS >(lhs.lhs() - other,
                             lhs.rhs());
      }

      // (ct_c1 + X) - c2 -> [ct_c1 - c2] + X
      template <long value, typename RHS, typename ScalarType, typename OtherScalarType, typename InterfaceType>
      ct_expr< constant<typename promote_traits<long, op_minus<ScalarType>, ScalarType>::result_type, InterfaceType >,
               op_plus<typename promote_traits<long, op_minus<ScalarType>, ScalarType>::result_type >,
               RHS >
      operator-(ct_expr<ct_constant<value>, op_plus<OtherScalarType>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<long, op_minus<ScalarType>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_plus<ScalarType>,
                       RHS >(result_constant(value - other),
                             lhs.rhs());
      }

      // (c1 - X) - c2 -> [c1 - c2] - X
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename T, typename InterfaceType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_minus<T>, ScalarType>::result_type >,
               op_minus<typename promote_traits<OtherScalarType, op_minus<T>, ScalarType>::result_type >,
               RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_minus<T>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_minus<T>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<typename promote_traits<OtherScalarType, op_minus<T>, ScalarType>::result_type >,
                       RHS >(lhs.lhs() - other,
                             lhs.rhs());
      }

      // (ct_c1 - X) - c2 -> [c1 - c2] - X
      template <long value, typename RHS, typename ScalarType, typename T, typename InterfaceType>
      ct_expr< constant<typename promote_traits<long, op_minus<T>, ScalarType>::result_type >,
               op_minus<typename promote_traits<long, op_minus<T>, ScalarType>::result_type>,
               RHS >
      operator-(ct_expr<ct_constant<value>, op_minus<T>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant< typename promote_traits<long, op_minus<T>, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<typename promote_traits<long, op_minus<T>, ScalarType>::result_type>,
                       RHS >(result_constant(value - other),
                             lhs.rhs());
      }

  
        // (c1 + X) + ct_c2 -> [c1 + ct_c2] + X
      template <typename ScalarType, typename OtherScalarType, typename RHS, long value, typename InterfaceType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type, InterfaceType>,
               op_plus<ScalarType>,
               RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_plus<ScalarType>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type, InterfaceType>    result_constant;
        return ct_expr<result_constant,
                       op_plus<ScalarType>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) + value),
                             lhs.rhs());
      }

  
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_mult<default_numeric_type>,
               constant<ScalarType, InterfaceType> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_mult<default_numeric_type>,
                       constant<ScalarType, InterfaceType> >(lhs, other);
      }
      
  
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_div<default_numeric_type>,
               constant<ScalarType, InterfaceType> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_div<default_numeric_type>,
                       constant<ScalarType, InterfaceType> >(lhs, other);
      }
      
  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator+(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value + other());
  }
  
  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator-(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value - other());
  }
  
  template <long value, typename OtherScalarType>
  constant<OtherScalarType>
  operator*(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    return constant<OtherScalarType>(value * other());
  }

  template <long value, typename OtherScalarType>
  constant<typename promote_traits<long, op_div<default_numeric_type>, OtherScalarType>::result_type>           
  operator/(ct_constant<value> const & lhs, 
            constant<OtherScalarType> const & other)
  {
    typedef typename promote_traits<long, op_div<default_numeric_type>, OtherScalarType>::result_type  result_type;
    
    return constant<result_type>(static_cast<result_type>(value) / static_cast<result_type>(other()));
  }
  
  
      
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

    
    template <typename ScalarType, typename InterfaceType>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_plus<typename InterfaceType::numeric_type>,
            variable<InterfaceType> >
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              variable<InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_plus<typename InterfaceType::numeric_type>,
                     variable<InterfaceType> >(lhs, other);
    }


    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator+(constant<ScalarType, InterfaceType> const & lhs,
              ct_variable<id> const & other)
    {
      return binary_expr<InterfaceType>(lhs.clone(),
                                        new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        new variable<InterfaceType>(id));
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator+(ct_variable<id> const & lhs,
              constant<ScalarType, InterfaceType> const & other)
    {
      return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                        new op_binary<op_plus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        other.clone());
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

    template <typename ScalarType, typename InterfaceType>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_minus<typename InterfaceType::numeric_type>,
            variable<InterfaceType> >
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              variable<InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_minus<typename InterfaceType::numeric_type>,
                     variable<InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator-(constant<ScalarType, InterfaceType> const & lhs,
              ct_variable<id> const & other)
    {
      return binary_expr<InterfaceType>(lhs.clone(),
                                        new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        new variable<InterfaceType>(id));
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator-(ct_variable<id> const & lhs,
              constant<ScalarType, InterfaceType> const & other)
    {
      return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                        new op_binary<op_minus<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        other.clone());
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
    
    template <typename ScalarType, typename InterfaceType>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_mult<typename InterfaceType::numeric_type>,
            variable<InterfaceType> >
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              variable<InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_mult<typename InterfaceType::numeric_type>,
                     variable<InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator*(constant<ScalarType, InterfaceType> const & lhs,
              ct_variable<id> const & other)
    {
      return binary_expr<InterfaceType>(lhs.clone(),
                                        new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        new variable<InterfaceType>(id));
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator*(ct_variable<id> const & lhs,
              constant<ScalarType, InterfaceType> const & other)
    {
      return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                        new op_binary<op_mult<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        other.clone());
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
    
    template <typename ScalarType, typename InterfaceType>
    ct_expr<constant<ScalarType, InterfaceType>,
            op_div<typename InterfaceType::numeric_type>,
            variable<InterfaceType> >
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              variable<InterfaceType> const & other)
    {
      return ct_expr<constant<ScalarType, InterfaceType>,
                     op_div<typename InterfaceType::numeric_type>,
                     variable<InterfaceType> >(lhs, other);
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator/(constant<ScalarType, InterfaceType> const & lhs,
              ct_variable<id> const & other)
    {
      return binary_expr<InterfaceType>(lhs.clone(),
                                        new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        new variable<InterfaceType>(id));
    }

    template <typename ScalarType, typename InterfaceType, id_type id>
    binary_expr<InterfaceType>
    operator/(ct_variable<id> const & lhs,
              constant<ScalarType, InterfaceType> const & other)
    {
      return binary_expr<InterfaceType>(new variable<InterfaceType>(id),
                                        new op_binary<op_div<typename InterfaceType::numeric_type>, InterfaceType>(),
                                        other.clone());
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