/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_COMPILE_TIME_CPP
#define VIENNAMATH_EXPRESSION_COMPILE_TIME_CPP

#include <ostream>

namespace viennamath
{
  
  //A compile time expression
  template <typename LHS,
            typename OP,
            typename RHS>
  class expression
  {
    public:
      typedef LHS    lhs_type;
      typedef OP     op_type;
      typedef RHS    rhs_type;
      
      explicit expression(LHS const & lhs, RHS const & rhs) : lhs_(lhs), rhs_(rhs) {}
      
      LHS const & lhs() const { return lhs_; }
      RHS const & rhs() const { return rhs_; }
    
    private:
      LHS const & lhs_;
      RHS const & rhs_;
  };
  
}

#endif