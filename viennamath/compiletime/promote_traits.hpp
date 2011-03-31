/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_PROMOTE_TRAITS_HPP
#define VIENNAMATH_PROMOTE_TRAITS_HPP

#include "viennamath/forwards.h"

namespace viennamath
{
   /** @brief For two numeric types T and U with objects t and u respectively, the result type of t+U is returned. Default case: return the basic numeric type for ViennaMath. */
   template <typename T, typename OP, typename U>
   struct promote_traits
   {
     typedef default_numeric_type  result_type;
   };

   /** @brief The result type of two operands of the same type is of the same type again (cf. standard C/C++ behavior for integers) */
   template <typename T, typename OP>
   struct promote_traits <T, OP, T>
   {
      typedef T      result_type;
   };
   
   //to double:
   template <typename OP>
   struct promote_traits <double, OP, long>
   {
      typedef double      result_type;
   };

   template <typename OP>
   struct promote_traits <long, OP, double>
   {
      typedef double      result_type;
   };

   template <typename OP>
   struct promote_traits <double, OP, int>
   {
      typedef double      result_type;
   };

   template <typename OP>
   struct promote_traits <int, OP, double>
   {
      typedef double      result_type;
   };
   
   template <typename OP>
   struct promote_traits <double, OP, float>
   {
      typedef double      result_type;
   };
   
   template <typename OP>
   struct promote_traits <float, OP, double>
   {
      typedef double      result_type;
   };
   
   //to float:
   template <typename OP>
   struct promote_traits <float, OP, long>
   {
      typedef float      result_type;
   };

   template <typename OP>
   struct promote_traits <long, OP, float>
   {
      typedef float      result_type;
   };
   
   template <typename OP>
   struct promote_traits <float, OP, int>
   {
      typedef float      result_type;
   };

   template <typename OP>
   struct promote_traits <int, OP, float>
   {
      typedef float      result_type;
   };
   
   //special case: integer division:
   template <typename NumericType>
   struct promote_traits <long, op_div<NumericType>, long>
   {
      typedef default_numeric_type      result_type;
   };

   template <typename NumericType>
   struct promote_traits <long, op_div<NumericType>, int>
   {
      typedef default_numeric_type      result_type;
   };
   
   template <typename NumericType>
   struct promote_traits <int, op_div<NumericType>, long>
   {
      typedef default_numeric_type      result_type;
   };
   
   
}

#endif