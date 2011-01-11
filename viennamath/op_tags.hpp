/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_OP_TAGS_HPP
#define VIENNAMATH_OP_TAGS_HPP

#include <string>
#include "viennamath/forwards.h"
#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  struct op_plus : public op_interface
  {
    //TODO: deduce return type
    template <typename LHS, typename RHS>
    static void apply(LHS const & lhs, RHS const & rhs) { return lhs + rhs; }
    
    
    //run time stuff:
    op_interface * clone() const { return new op_plus(); }
    std::string print() const { return "+"; }
    
  };
  
}

#endif