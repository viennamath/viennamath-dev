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
//#include "viennamath/runtime/constant.hpp"
//#include "viennamath/runtime/variable.hpp"
#include "viennamath/compiletime/ct_expr.hpp"
//#include "viennamath/runtime/binary_operators.hpp"

namespace viennamath
{
  /////////////////////////////////// operator+ ///////////////////////////////////
  
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
      ct_expr< rt_constant<typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type >,
                 op_minus<ScalarType>,
                 RHS >
      operator+(ct_expr<rt_constant<OtherScalarType>, op_minus<ScalarType>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef rt_constant< typename promote_traits<OtherScalarType, op_plus<ScalarType>, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<ScalarType>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) + value),
                             lhs.rhs());
      }
  

  /////////////////////////////////// operator- ///////////////////////////////////

      // (A + B) - A  -> B, where A is an variable:
      template <typename ScalarType, unsigned long id, typename RHS>
      RHS
      operator-(ct_expr<ct_variable<id>, op_plus<ScalarType>, RHS> const & lhs,
                ct_variable<id> const & other)
      {
        return lhs.rhs();
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
      ct_expr< rt_constant<typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >,
               op_plus<T>,
               RHS >
      operator-(ct_expr<rt_constant<OtherScalarType>, op_plus<T>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef rt_constant< typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >    result_constant;
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
      ct_expr< rt_constant<typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >,
                 op_minus<T>,
                 RHS >
      operator-(ct_expr<rt_constant<OtherScalarType>, op_minus<T>, RHS> const & lhs,
                ct_constant<value> const & other)
      {
        typedef rt_constant< typename promote_traits<OtherScalarType, op_plus<T>, long>::result_type >    result_constant;
        return ct_expr<result_constant,
                       op_minus<T>,
                       RHS >(result_constant(static_cast<OtherScalarType>(lhs.lhs()) - value),
                             lhs.rhs());
      }
  


  /////////////////////////////////// operator* ///////////////////////////////////



  /////////////////////////////////// operator/ ///////////////////////////////////

      //division of the same thing leads to '1':
      template <typename LHS, typename OP, typename RHS>
      ct_constant<1>
      operator/(ct_expr<LHS, OP, RHS> const & lhs,
                ct_expr<LHS, OP, RHS> const & other)
      {
        return ct_constant<1>();
      }
  
}

#endif