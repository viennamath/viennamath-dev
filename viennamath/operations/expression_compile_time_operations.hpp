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
#include "viennamath/op_tags.hpp"

namespace viennamath
{
  /////////////////////////////////// operator+ ///////////////////////////////////
  
      template <typename LHS, typename OP, typename RHS,
                typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_plus,
                 ct_expr<LHS2, OP2, RHS2> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_plus,
                          ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, unsigned long id>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_plus,
                 variable<id> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_plus,
                          variable<id> >(lhs, other);
      }
      
      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_plus,
                 constant<ScalarType> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_plus,
                          constant<ScalarType> >(lhs, other);
      }

      // (c1 + X) + c2 -> [c1 + c2] + X
      template <typename OtherScalarType, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, ScalarType>::result_type >,
                 op_plus,
                 RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_plus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(lhs.lhs() + other,
                                lhs.rhs());
      }

      // (ct_c1 + X) + c2 -> [ct_c1 + c2] + X
      template <long value, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<long, op_plus, ScalarType>::result_type >,
                 op_plus,
                 RHS >
      operator+(ct_expr<ct_constant<value>, op_plus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<long, op_plus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(result_constant(value + other),
                                lhs.rhs());
      }


      // (c1 - X) + c2 -> [c1 + c2] - X
      template <typename OtherScalarType, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, ScalarType>::result_type >,
                 op_minus,
                 RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_minus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(lhs.lhs() + other,
                                lhs.rhs());
      }

      // (ct_c1 - X) + c2 -> [ct_c1 + c2] - X
      template <long value, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<long, op_plus, ScalarType>::result_type >,
                 op_minus,
                 RHS >
      operator+(ct_expr<ct_constant<value>, op_minus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<long, op_plus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(result_constant(value + other),
                                lhs.rhs());
      }

      //with ct_constant:
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_plus,
                 ct_constant<value> >
      operator+(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_plus,
                          ct_constant<value> >(lhs, other);
      }
      
      
      // (ct_c1 + X) + ct_c2 -> [ct_c1 + ct_c2] + X
      template <long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 + value_2 >,
                 op_plus,
                 RHS >
      operator+(ct_expr<ct_constant<value_1>, op_plus, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 + value_2 >,
                          op_plus,
                          RHS >(ct_constant< value_1 + value_2 >(),
                                lhs.rhs());
      }

      // (c1 + X) + ct_c2 -> [c1 + ct_c2] + X
      template <typename OtherScalarType, typename RHS, long value>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, long>::result_type >,
                 op_plus,
                 RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_plus, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) + value),
                                lhs.rhs());
      }

      // (ct_c1 - X) + ct_c2 -> [ct_c1 + ct_c2] - X
      template <long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 + value_2 >,
                 op_minus,
                 RHS >
      operator+(ct_expr<ct_constant<value_1>, op_minus, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 + value_2 >,
                          op_minus,
                          RHS >(ct_constant< value_1 + value_2 >(),
                                lhs.rhs());
      }

      // (c1 - X) + ct_c2 -> [c1 + ct_c2] - X
      template <typename OtherScalarType, typename RHS, long value>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, long>::result_type >,
                 op_minus,
                 RHS >
      operator+(ct_expr<constant<OtherScalarType>, op_minus, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) + value),
                                lhs.rhs());
      }
  

  /////////////////////////////////// operator- ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_minus,
                 ct_expr<LHS2, OP2, RHS2> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_minus,
                          ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }

      //with variable:
      template <typename LHS, typename OP, typename RHS, unsigned long id>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_minus,
                 variable<id> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_minus,
                          variable<id> >(lhs, other);
      }

      // (A + B) - A  -> B, where A is an variable:
      template <unsigned long id, typename RHS>
      RHS
      operator-(ct_expr<variable<id>, op_plus, RHS> const & lhs,
                variable<id> const & other)
      {
        return lhs.rhs();
      }
      

      //with constant:
      template <typename LHS, typename OP, typename RHS, typename ScalarType>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_minus,
                 constant<ScalarType> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_minus,
                          constant<ScalarType> >(lhs, other);
      }
      
      // (c1 + X) - c2 -> [c1 - c2] + X
      template <typename OtherScalarType, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_minus, ScalarType>::result_type >,
                 op_plus,
                 RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_plus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_minus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(lhs.lhs() - other,
                                lhs.rhs());
      }

      // (ct_c1 + X) - c2 -> [ct_c1 - c2] + X
      template <long value, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<long, op_minus, ScalarType>::result_type >,
                 op_plus,
                 RHS >
      operator-(ct_expr<ct_constant<value>, op_plus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<long, op_minus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(result_constant(value - other),
                                lhs.rhs());
      }

      // (c1 - X) - c2 -> [c1 - c2] - X
      template <typename OtherScalarType, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_minus, ScalarType>::result_type >,
                 op_minus,
                 RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_minus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_minus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(lhs.lhs() - other,
                                lhs.rhs());
      }

      // (ct_c1 - X) - c2 -> [c1 - c2] - X
      template <long value, typename RHS, typename ScalarType>
      ct_expr< constant<typename promote_traits<long, op_minus, ScalarType>::result_type >,
                 op_minus,
                 RHS >
      operator-(ct_expr<ct_constant<value>, op_minus, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        typedef constant< typename promote_traits<long, op_minus, ScalarType>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(result_constant(value - other),
                                lhs.rhs());
      }

      
      //with ct_constant:
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_minus,
                 ct_constant<value> >
      operator-(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_minus,
                          ct_constant<value> >(lhs, other);
      }
      

      // (ct_c1 + X) - ct_c2 -> [ct_c1 - ct_c2] + X
      template <long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 - value_2 >,
                 op_plus,
                 RHS >
      operator-(ct_expr<ct_constant<value_1>, op_plus, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 - value_2 >,
                          op_plus,
                          RHS >(ct_constant< value_1 - value_2 >(),
                                lhs.rhs());
      }

      // (c1 + X) - ct_c2 -> [c1 - ct_c2] + X
      template <typename OtherScalarType, typename RHS, long value>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, long>::result_type >,
                 op_plus,
                 RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_plus, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_plus,
                          RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) - value),
                                lhs.rhs());
      }

      // (ct_c1 - X) - ct_c2 -> [ct_c1 - ct_c2] - X
      template <long value_1, typename RHS, long value_2>
      ct_expr<ct_constant< value_1 - value_2 >,
                 op_minus,
                 RHS >
      operator-(ct_expr<ct_constant<value_1>, op_minus, RHS> const & lhs,
                ct_constant<value_2> const & other)
      {
        return ct_expr<ct_constant< value_1 - value_2 >,
                          op_minus,
                          RHS >(ct_constant< value_1 - value_2 >(),
                                lhs.rhs());
      }

      // (c1 - X) - ct_c2 -> [c1 - ct_c2] - X
      template <typename OtherScalarType, typename RHS, long value>
      ct_expr< constant<typename promote_traits<OtherScalarType, op_plus, long>::result_type >,
                 op_minus,
                 RHS >
      operator-(ct_expr<constant<OtherScalarType>, op_minus, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef constant< typename promote_traits<OtherScalarType, op_plus, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                          op_minus,
                          RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) - value),
                                lhs.rhs());
      }
  


  /////////////////////////////////// operator* ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_mult,
                 ct_expr<LHS2, OP2, RHS2> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_mult,
                          ct_expr<LHS2, OP2, RHS2> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, unsigned long id>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_mult,
                 variable<id> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_mult,
                          variable<id> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, typename ScalarType>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_mult,
                 constant<ScalarType> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_mult,
                          constant<ScalarType> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_mult,
                 ct_constant<value> >
      operator*(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_mult,
                          ct_constant<value> >(lhs, other);
      }




  /////////////////////////////////// operator/ ///////////////////////////////////

      template <typename LHS, typename OP, typename RHS, typename LHS2, typename OP2, typename RHS2>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_div,
                 ct_expr<LHS2, OP2, RHS2> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_div,
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
      
      template <typename LHS, typename OP, typename RHS, unsigned long id>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_div,
                 variable<id> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                variable<id> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_div,
                          variable<id> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, typename ScalarType>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_div,
                 constant<ScalarType> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                constant<ScalarType> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_div,
                          constant<ScalarType> >(lhs, other);
      }
      
      template <typename LHS, typename OP, typename RHS, long value>
      ct_expr<ct_expr<LHS, OP, RHS>,
                 op_div,
                 ct_constant<value> >
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        return ct_expr<ct_expr<LHS, OP, RHS>,
                          op_div,
                          ct_constant<value> >(lhs, other);
      }
  
}

#endif