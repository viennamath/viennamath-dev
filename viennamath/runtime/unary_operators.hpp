#ifndef VIENNAMATH_RUNTIME_UNARY_OPERATORS_HPP
#define VIENNAMATH_RUNTIME_UNARY_OPERATORS_HPP

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
#include "viennamath/compiletime/unary_op_tags.hpp"

namespace viennamath
{
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_id<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_exp<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sin<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_cos<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_tan<NumericT>,  const InterfaceType * diff_var);
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_fabs<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_sqrt<NumericT>, const InterfaceType * diff_var);
  
  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log<NumericT>, const InterfaceType * diff_var);

  template <typename InterfaceType, typename NumericT>
  InterfaceType * diff_impl(const InterfaceType * e, op_log10<NumericT>, const InterfaceType * diff_var);

  
  template <typename T>
  bool unary_op_equal(T const & lhs, T const & rhs) { return true; }
  
  //
  // main class for all unary operations:
  // 
  template <typename unary_operation, typename InterfaceType>
  class op_unary : public op_interface<InterfaceType>
  {
    public: 
      typedef typename InterfaceType::numeric_type    numeric_type;
      //TODO: deduce return type
      //template <typename LHS, typename RHS>
      //static void apply(LHS const & lhs, RHS const & rhs) { return lhs; }
      
      op_unary() {}
      
      op_unary(unary_operation const & uo) : unary_op_(uo) {}
      
      unary_operation const & op() const { return unary_op_; }
      
      //run time stuff:
      std::string str() const { return unary_op_.str(); }
      op_interface<InterfaceType> * clone() const { return new op_unary<unary_operation, InterfaceType>(unary_op_); }
      numeric_type apply(numeric_type value) const { return unary_op_.apply(value); }
      numeric_type apply(numeric_type lhs, numeric_type rhs) const { return unary_op_.apply(lhs); }
      bool is_unary() const { return true; }
      
      InterfaceType * diff(const InterfaceType * e,
                           const InterfaceType * diff_var) const
      {
        return diff_impl(e, unary_op_, diff_var);
      }

      InterfaceType * diff(const InterfaceType * lhs,
                           const InterfaceType * rhs,
                           const InterfaceType * diff_var) const
      {
        return diff_impl(lhs, unary_op_, diff_var);
      }

      InterfaceType * optimize(const InterfaceType * lhs,
                                const InterfaceType * rhs) const;

      bool optimizable() const { return unary_op_.optimizable(); }
      
      bool equal(const op_interface<InterfaceType> * other) const
      {
        const op_unary<unary_operation, InterfaceType> * ptr = dynamic_cast<const op_unary<unary_operation, InterfaceType> *>(other);
        if (ptr != NULL)
          return unary_op_equal(ptr->op(), unary_op_); //needed for partial derivatives
          
        return false; 
      }
      
    
    private:
      //We use an unary_operation member, because the unary_operation tag might have a state -> pure static tag dispatch not enough then
      unary_operation unary_op_;
  };


}

#endif