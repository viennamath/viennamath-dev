/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_COMPILE_TIME_OPERATIONS_CPP
#define VIENNAMATH_EXPRESSION_COMPILE_TIME_OPERATIONS_CPP

#include "viennamath/forwards.h"
#include "viennamath/constant.hpp"
#include "viennamath/variable.hpp"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/binary_operators.hpp"

namespace viennamath
{
  /////////////////////////////////// operator+ ///////////////////////////////////
  
      template <typename LHS, typename OP, typename RHS,
                typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_plus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
              ct_expr<LHS2, OP2, RHS2> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_plus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
                       ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, unsigned long id, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_plus<typename InterfaceType::numeric_type>,
              variable<id, InterfaceType> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_plus<typename InterfaceType::numeric_type>,
                       variable<id, InterfaceType> >(lhs, other);
      }
      
      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_plus<typename InterfaceType::numeric_type>,
              constant<ScalarType, InterfaceType> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_plus<typename InterfaceType::numeric_type>,
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
      ct_expr< constant<typename InterfaceType::numeric_type, InterfaceType>,
               op_minus<typename InterfaceType::numeric_type>,
               RHS >
      operator+(ct_expr<constant<OtherScalarType, InterfaceType>, op_minus<typename InterfaceType::numeric_type>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant<typename InterfaceType::numeric_type, InterfaceType>    result_constant;
        
        return ct_expr<result_constant,
                       op_minus<typename InterfaceType::numeric_type>,
                       RHS >(result_constant(lhs.lhs().unwrap() + other.unwrap()),
                             lhs.rhs());
      }

      // (ct_c1 - X) + c2 -> [ct_c1 + c2] - X
      template <long value, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr< constant<typename InterfaceType::numeric_type, InterfaceType >,
               op_minus<typename InterfaceType::numeric_type>,
               RHS >
      operator+(ct_expr<ct_constant<value>, op_minus<typename InterfaceType::numeric_type>, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        typedef constant<ScalarType, InterfaceType>    result_constant;
        return ct_expr<result_constant,
                       op_minus<typename InterfaceType::numeric_type>,
                       RHS >(result_constant(value + other),
                             lhs.rhs());
      }

      //with ct_constant:
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_plus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
              ct_constant<value> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_plus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
                       ct_constant<value> >(lhs, other);
      }
      
      
      // (ct_c1 + X) + ct_c2 -> [ct_c1 + ct_c2] + X
      template <typename ScalarType, long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 + value_2 >,
              op_plus<ScalarType>,
              RHS >
      operator+(ct_expr<ct_constant<value_1>, op_plus<ScalarType>, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 + value_2 >,
                       op_plus<ScalarType>,
                       RHS >(ct_constant< value_1 + value_2 >(),
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

      // (ct_c1 - X) + ct_c2 -> [ct_c1 + ct_c2] - X
      template <typename ScalarType, long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 + value_2 >,
              op_minus<ScalarType>,
              RHS >
      operator+(ct_expr<ct_constant<value_1>, op_minus<ScalarType>, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 + value_2 >,
                       op_minus<ScalarType>,
                       RHS >(ct_constant< value_1 + value_2 >(),
                             lhs.rhs());
      }

      // (c1 - X) + ct_c2 -> [c1 + ct_c2] - X
      template <typename ScalarType, typename OtherScalarType, typename RHS, long value>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type >,
                 op_minus<ScalarType>,
                 RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_minus<ScalarType>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<ScalarType>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) + value),
                             lhs.rhs());
      }
  

  /////////////////////////////////// operator- ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_minus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
              ct_expr<LHS2, OP2, RHS2> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_minus<typename ct_expr<LHS, OP, RHS>::numeric_type>,
                       ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }

      //with variable:
      template <typename LHS, typename OP, typename RHS, unsigned long id, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_minus<typename InterfaceType::numeric_type>,
              variable<id, InterfaceType> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_minus<typename InterfaceType::numeric_type>,
                       variable<id, InterfaceType> >(lhs, other);
      }

      // (A + B) - A  -> B, where A is an variable:
      template <typename ScalarType, unsigned long id, typename RHS, typename InterfaceType>
      RHS
      operator-(ct_expr<variable<id, InterfaceType>, op_plus<ScalarType>, RHS> const & lhs,
                variable<id, InterfaceType> const & other)
      {
        return lhs.rhs();
      }
      

      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType, typename InterfaceType>
      ct_expr<ct_expr<LHS, OP, RHS>,
              op_minus< typename InterfaceType::numeric_type >,
              constant<ScalarType, InterfaceType> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_minus< typename InterfaceType::numeric_type >,
                       constant<ScalarType, InterfaceType> >(lhs, other);
      }
      
      // (c1 + X) - c2 -> [c1 - c2] + X
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename InterfaceType, typename T>
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
      template <typename OtherScalarType, typename RHS, typename ScalarType, typename InterfaceType, typename T>
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

      
      //with ct_constant:
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_minus<default_numeric_type>,
               ct_constant<value> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_minus<default_numeric_type>,
                       ct_constant<value> >(lhs, other);
      }
      

      // (ct_c1 + X) - ct_c2 -> [ct_c1 - ct_c2] + X
      template <long value_1, typename RHS, long value_2, typename T>
      ct_expr< ct_constant< value_1 - value_2 >,
               op_plus<T>,
               RHS >
      operator-(ct_expr<ct_constant<value_1>, op_plus<T>, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 - value_2 >,
                       op_plus<T>,
                       RHS >(ct_constant< value_1 - value_2 >(),
                             lhs.rhs());
      }

      // (c1 + X) - ct_c2 -> [c1 - ct_c2] + X
      template <typename OtherScalarType, typename RHS, long value, typename T>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >,
               op_plus<T>,
               RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_plus<T>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_plus<T>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) - value),
                             lhs.rhs());
      }

      // (ct_c1 - X) - ct_c2 -> [ct_c1 - ct_c2] - X
      template <long value_1, typename RHS, long value_2, typename T>
      ct_expr< ct_constant< value_1 - value_2 >,
               op_minus<T>,
               RHS >
      operator-(ct_expr<ct_constant<value_1>, op_minus<T>, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 - value_2 >,
                       op_minus<T>,
                       RHS >(ct_constant< value_1 - value_2 >(),
                             lhs.rhs());
      }

      // (c1 - X) - ct_c2 -> [c1 - ct_c2] - X
      template <typename OtherScalarType, typename RHS, long value, typename T>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >,
                 op_minus<T>,
                 RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_minus<T>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<T>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) - value),
                             lhs.rhs());
      }
  


  /////////////////////////////////// operator* ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_mult<default_numeric_type>,
               ct_expr<LHS2, OP2, RHS2> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_mult<default_numeric_type>,
                       ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, unsigned long id, typename InterfaceType>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_mult<default_numeric_type>,
               variable<id, InterfaceType> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_mult<default_numeric_type>,
                       variable<id, InterfaceType> >(lhs, other);
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
      
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_mult<default_numeric_type>,
               ct_constant<value> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_mult<default_numeric_type>,
                       ct_constant<value> >(lhs, other);
      }




  /////////////////////////////////// operator/ ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_div<default_numeric_type>,
               ct_expr<LHS2, OP2, RHS2> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_div<default_numeric_type>,
                       ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }
      
      //division of the same thing leads to '1':
      template <typename LHS, typename OP, typename RHS>
      ct_constant<1>
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS, OP, RHS> const & other)
      {
        return ct_constant<1>();
      }
      
      template <typename LHS, typename OP, typename RHS, unsigned long id, typename InterfaceType>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_div<default_numeric_type>,
               variable<id, InterfaceType> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id, InterfaceType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_div<default_numeric_type>,
                       variable<id> >(lhs, other);
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
      
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr< ct_expr<LHS, OP, RHS>,
               op_div<default_numeric_type>,
               ct_constant<value> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                       op_div<default_numeric_type>,
                       ct_constant<value> >(lhs, other);
      }
  
}

#endif