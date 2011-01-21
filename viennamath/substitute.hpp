/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_SUBSTITUTE_HPP
#define VIENNAMATH_SUBSTITUTE_HPP

#include "viennamath/forwards.h"
#include "viennamath/binary_expression_operations.hpp"

namespace viennamath
{
  
  
  
  
  
  
  
  
  //public interface:
  /** @brief Replaces all occurances of the unknown u in the expression 'e' with 'u'. */
  template <typename ScalarType, unsigned long id, typename ReplacementType, typename ExpressionType>
  binary_expr substitute(unknown<ScalarType, id> const & u,
                  ReplacementType const & repl,
                  ExpressionType const & e)
  {
    //generic approach: use operator() and hope the best:
    return e.substitute(u, repl);
  }

  

}

#endif