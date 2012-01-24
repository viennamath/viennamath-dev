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
      
    ////////////////// Operations //////////////////////////////
    
    ////// operator+


    // c1 + (c2 + X) -> [c1 + c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<rt_constant<OtherScalarType, InterfaceType>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 + (ct_c2 + X) -> [c1 + ct_c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + value),
                      other.rhs());
    }

    // c1 + (c2 - X) -> [c1 + c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<rt_constant<OtherScalarType, InterfaceType>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 + (ct_c2 - X) -> [c1 + ct_c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator+(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_plus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) + value),
                      other.rhs());
    }

    
    // (ct_c1 + X) + c2 -> [ct_c1 + c2] + X
    template <long value, typename RHS, typename ScalarType, typename T, typename InterfaceType>
    ct_expr< rt_constant<typename promote_traits<long, op_plus<T>, ScalarType>::result_type >,
              op_plus<T>,
              RHS >
    operator+(ct_expr<ct_constant<value>, op_plus<T>, RHS> const & lhs,
              rt_constant<ScalarType, InterfaceType> const & other)
    {
      typedef rt_constant< typename promote_traits<long, op_plus<T>, ScalarType>::result_type >    result_constant;
      return ct_expr<result_constant,
                      op_plus<T>,
                      RHS >(result_constant(value + static_cast<ScalarType>(other)),
                            lhs.rhs());
    }

    // (ct_c1 - X) + c2 -> [ct_c1 + c2] - X
    template <long value, typename RHS, typename ScalarType, typename InterfaceType>
    ct_expr< rt_constant<default_numeric_type, InterfaceType >,
              op_minus<default_numeric_type>,
              RHS >
    operator+(ct_expr<ct_constant<value>, op_minus<default_numeric_type>, RHS> const & lhs,
              rt_constant<ScalarType, InterfaceType> const & other)
    {
      typedef rt_constant<ScalarType, InterfaceType>    result_constant;
      return ct_expr<result_constant,
                      op_minus<default_numeric_type>,
                      RHS >(result_constant(value + other),
                            lhs.rhs());
    }

    
    
    ////// operator-
    
    // c1 - (c2 + X) -> [c1 - c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<rt_constant<OtherScalarType, InterfaceType>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 - (ct_c2 + X) -> [c1 - ct_c2] - X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_minus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_plus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_minus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - value),
                      other.rhs());
    }

    // c1 - (c2 - X) -> [c1 - c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, typename OtherScalarType, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<rt_constant<OtherScalarType, InterfaceType>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, OtherScalarType>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - static_cast<OtherScalarType>(other.lhs())),
                      other.rhs());
    }

    // c1 - (ct_c2 - X) -> [c1 - ct_c2] + X, where X is anything:
    template <typename ScalarType, typename InterfaceType, long value, typename RHS>
    ct_expr<rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >,
            op_plus<typename InterfaceType::numeric_type>,
            RHS >
    operator-(rt_constant<ScalarType, InterfaceType> const & lhs,
              ct_expr<ct_constant<value>, op_minus<typename InterfaceType::numeric_type>, RHS> const & other)
    {
      typedef rt_constant<typename promote_traits<ScalarType, op_minus<typename InterfaceType::numeric_type>, long>::result_type, InterfaceType >  ret_constant;
      return ct_expr<ret_constant,
                     op_plus<typename InterfaceType::numeric_type>,
                     RHS
                    >(ret_constant(static_cast<ScalarType>(lhs) - value),
                      other.rhs());
    }

  

    /////////// operator*

    /////////// operator/ 
  
}

#endif