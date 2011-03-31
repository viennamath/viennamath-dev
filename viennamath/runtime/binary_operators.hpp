/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_BINARY_OPERATORS_HPP
#define VIENNAMATH_BINARY_OPERATORS_HPP

#include <string>
#include <vector>
#include <math.h>
#include "viennamath/forwards.h"
#include "viennamath/runtime/op_interface.hpp"
#include "viennamath/compiletime/binary_op_tags.hpp"

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

      bool equal(const op_interface<InterfaceType> * other) const
      {
        return (dynamic_cast<const op_binary<BinaryOperation, InterfaceType> *>(other) != NULL); 
      }
      
  };
  
  
  
  
}

#endif