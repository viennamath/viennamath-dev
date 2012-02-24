#ifndef VIENNAMATH_RUNTIME_BINARY_OPERATORS_HPP
#define VIENNAMATH_RUNTIME_BINARY_OPERATORS_HPP

/* =======================================================================
   Copyright (c) 2012, Institute for Microelectronics,
                       Institute for Analysis and Scientific Computing,
                       TU Wien.
                             -----------------
               ViennaMath - Symbolic and Numerical Math in C++
                             -----------------

   Author:     Karl Rupp                          rupp@iue.tuwien.ac.at

   License:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */




#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/runtime/op_interface.hpp"
#include "viennamath/compiletime/binary_op_tags.hpp"

/** @file binary_operators.hpp
    @brief Defines the binary operation class wrapping all binary operation tags at runtime.
*/

namespace viennamath
{
  
  //differentiation:
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs, const InterfaceType * diff_var);
  
  
  //optimization:
  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * optimize_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs);
  
  
  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_plus<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_minus<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_mult<NumericT>, const InterfaceType * rhs);

  template <typename InterfaceType, typename NumericT>
  bool optimizable_impl(const InterfaceType * lhs, op_div<NumericT>, const InterfaceType * rhs);
  
  
  //////////////////////////////////////// binary operators ////////////////////////////////////////
  
  
  template <typename BinaryOperation, typename InterfaceType>
  class op_binary : public op_interface<InterfaceType>
  {
    public: 
      typedef typename InterfaceType::numeric_type         numeric_type;
      
      //run time stuff:
      std::string str() const { return BinaryOperation::str(); }
      op_interface<InterfaceType> * clone() const { return new op_binary<BinaryOperation, InterfaceType>(); }
      numeric_type apply(numeric_type lhs, numeric_type rhs) const { return BinaryOperation::apply(lhs, rhs); }
      bool is_unary() const { return false; }
      
      InterfaceType * diff(const InterfaceType * lhs,
                           const InterfaceType * rhs,
                           const InterfaceType * diff_var) const
      {
        return diff_impl(lhs, BinaryOperation(), rhs, diff_var);
      }
      
      InterfaceType * optimize(const InterfaceType * lhs,
                                const InterfaceType * rhs) const
      {
        return optimize_impl(lhs, BinaryOperation(), rhs);
      }

      bool optimizable(const InterfaceType * lhs,
                       const InterfaceType * rhs) const
      {
        return optimizable_impl(lhs, BinaryOperation(), rhs);
      }
      
      bool optimizable() const { throw "must not be reached - just for unary_expr"; }      

      bool equal(const op_interface<InterfaceType> * other) const
      {
        return (dynamic_cast<const op_binary<BinaryOperation, InterfaceType> *>(other) != NULL); 
      }
      
  };
  
  
  
  
}

#endif