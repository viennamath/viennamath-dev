/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_MANIPULATION_OPTIMIZE_HPP
#define VIENNAMATH_MANIPULATION_OPTIMIZE_HPP

#include "viennamath/forwards.h"
#include "viennamath/runtime/functor_wrapper.hpp"
#include <assert.h>

namespace viennamath
{
  
  //
  //   Section 1: Compile time optimization
  //
  
  //TODO: compile time substitution
  
  
  
  //
  //   Section 1: Run time optimization
  //
  
  
  
  //public interface:
  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_expr<InterfaceType> & e)
  {
    while (e.get()->optimizable())
      e = e.get()->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_unary_expr<InterfaceType> & e)
  {
    while (e->optimizable())
      e = e->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename InterfaceType>
  void inplace_optimize(rt_binary_expr<InterfaceType> & e)
  {
    while (e->optimizable())
      e = e->optimize();
  }

  /** @brief Optimizes an expression. */
  template <typename T>
  void inplace_optimize(T & e)
  {
    //do nothing, since primitive types cannot be simplified
  }

}

#endif