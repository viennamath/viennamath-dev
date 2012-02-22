#ifndef VIENNAMATH_COMPILETIME_CT_BINARY_EXPR_HPP
#define VIENNAMATH_COMPILETIME_CT_BINARY_EXPR_HPP

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




#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/binary_op_tags.hpp"

namespace viennamath
{
  
  //A compile time expression
  template <typename LHS,
            typename OP,
            typename RHS>
  class ct_binary_expr
  {
      typedef typename expression_traits<LHS>::const_reference_type    internal_lhs_type;
      typedef typename expression_traits<RHS>::const_reference_type    internal_rhs_type;
    public:
      typedef typename OP::numeric_type            numeric_type;
      
      typedef LHS    lhs_type;
      typedef OP     op_type;
      typedef RHS    rhs_type;
      
      explicit ct_binary_expr() : lhs_(LHS()), rhs_(RHS()) {} 
      
      explicit ct_binary_expr(internal_lhs_type lhs,
                              internal_rhs_type rhs) : lhs_(lhs), rhs_(rhs) {}
                          
      internal_lhs_type lhs() const { return lhs_; }
      internal_rhs_type rhs() const { return rhs_; }
      
      template <typename VectorType>
      numeric_type operator()(VectorType const & v) const
      {
        //std::cout << "ct_expr::operator()" << std::endl;
        return OP::apply(static_cast<numeric_type>(lhs_(v)), static_cast<numeric_type>(rhs_(v)));
      }

    private:
      internal_lhs_type lhs_;
      internal_rhs_type rhs_;
  };
  
  
  //stream operator for output:
  template <typename LHS, typename OP, typename RHS>
  std::ostream& operator<<(std::ostream & stream, ct_binary_expr<LHS, OP, RHS> const & other)
  {
    stream << "[" << other.lhs() << OP().str() << other.rhs() << "]";
    return stream;
  }

  
}

#endif