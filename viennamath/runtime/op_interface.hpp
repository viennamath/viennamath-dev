#ifndef VIENNAMATH_RUNTIME_OP_INTERFACE_HPP
#define VIENNAMATH_RUNTIME_OP_INTERFACE_HPP

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




#include <vector>
#include <exception>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  struct ex_no_rhs_provided  : std::exception
  {
    const char* what() const throw() { return "Error due to wrong use of class 'op_interface': No right hand side provided for binary operator."; }
  };
  
  struct ex_rhs_provided_for_unary_operator : std::exception
  {
    const char* what() const throw() { return "Error due to wrong use of class 'op_interface': A right hand side argument was provided to an unary operator."; }
  };
  
  
  template <typename InterfaceType>
  class op_interface
  {
    public:
      typedef typename InterfaceType::numeric_type       numeric_type;
      
      virtual ~op_interface() {}
      
      /** @brief The operator returns a pointer to a copy of itself */
      virtual op_interface * clone() const = 0;
      
      /** @brief Returns an identification string describing the operator, e.g. exp, sin, cos, ... */
      virtual std::string    str() const = 0;

      /** @brief Applys the operator to the provided value. Unary operators must overwrite this function. */
      virtual numeric_type   apply(numeric_type value) const { throw ex_no_rhs_provided(); }                   
      
      /** @brief Applys the operator to the left hand side 'lhs' and the right hand side 'rhs'. Binary operators must overwrite this function. */
      virtual numeric_type   apply(numeric_type lhs,
                                   numeric_type rhs) const { throw ex_rhs_provided_for_unary_operator(); }

      /** @brief A boolean flag that specifies whether the operator is an unary operator, i.e. taking one argument only */                             
      virtual bool                   is_unary() const { return true; }

      //unary diff:
      virtual InterfaceType * diff(const InterfaceType * e,
                                   const InterfaceType * diff_var) const { throw ex_no_rhs_provided(); }

      //binary diff:                                   
      virtual InterfaceType * diff(const InterfaceType * lhs,
                                   const InterfaceType * rhs,
                                   const InterfaceType * diff_var) const { throw ex_rhs_provided_for_unary_operator(); }
                                   
      //optimization for binary operators:
      virtual InterfaceType * optimize(const InterfaceType * lhs,
                                       const InterfaceType * rhs) const = 0; //{ throw ex_rhs_provided_for_unary_operator(); }

      //optimization for unary operators:
      //virtual InterfaceType * optimize(const InterfaceType * lhs) const { return lhs->optimize(); }
      virtual bool optimizable() const = 0;
      virtual bool optimizable(const InterfaceType * lhs,
                               const InterfaceType * rhs) const { return false; }    
                               
      virtual bool equal(const op_interface * other) const = 0;
  };
  
  

  
}

#endif