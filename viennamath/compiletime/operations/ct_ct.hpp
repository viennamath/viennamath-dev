/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_COMPILETIME_OPERATIONS_CT_CT_HPP
#define VIENNAMATH_COMPILETIME_OPERATIONS_CT_CT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/ct_constant.hpp"
#include "viennamath/compiletime/ct_variable.hpp"
#include "viennamath/compiletime/ct_expr.hpp"

namespace viennamath
{
  
  namespace result_of
  {
    
    template <typename LHS, typename RHS>
    struct add<LHS, RHS, true, true>
    {
      typedef ct_expr<LHS,
                      op_plus<default_numeric_type>,
                      RHS >              type;
                      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(); }                
    };

    template <typename LHS, typename RHS>
    struct subtract<LHS, RHS, true, true>
    {
      typedef ct_expr<LHS,
                      op_minus<default_numeric_type>,
                      RHS >              type;
                      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(); }                
    };

    template <typename LHS, typename RHS>
    struct mult<LHS, RHS, true, true>
    {
      typedef ct_expr<LHS,
                      op_mult<default_numeric_type>,
                      RHS >              type;
                      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(); }                
    };

    template <typename LHS, typename RHS>
    struct div<LHS, RHS, true, true>
    {
      typedef ct_expr<LHS,
                      op_div<default_numeric_type>,
                      RHS >              type;
                      
      static type instance(LHS const & lhs, RHS const & rhs) { return type(); }                
    };
    
  }
  
  
  
  
}

#endif