/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNARY_OPERATORS_HPP
#define VIENNAMATH_UNARY_OPERATORS_HPP

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
      
      
      //run time stuff:
      std::string str() const { return unary_operation::str(); }
      op_interface<InterfaceType> * clone() const { return new op_unary<unary_operation, InterfaceType>(); }
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

      bool equal(const op_interface<InterfaceType> * other) const
      {
        return (dynamic_cast<const op_unary<unary_operation, InterfaceType> *>(other) != NULL); 
      }
      
    
    private:
      //We use an unary_operation member, because the unary_operation tag might have a state -> pure static tag dispatch not enough then
      unary_operation unary_op_;
  };

  
  
}

#endif