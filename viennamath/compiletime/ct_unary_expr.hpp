#ifndef VIENNAMATH_COMPILETIME_CT_UNARY_EXPR_HPP
#define VIENNAMATH_COMPILETIME_CT_UNARY_EXPR_HPP

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
#include "viennamath/compiletime/unary_op_tags.hpp"

namespace viennamath
{
  
  //A compile time expression
  template <typename LHS,
            typename OP>
  class ct_unary_expr
  {
      typedef typename expression_traits<LHS>::const_reference_type    internal_lhs_type;
    public:
      typedef typename OP::numeric_type            numeric_type;
      
      typedef LHS    lhs_type;
      typedef OP     op_type;
      
      explicit ct_unary_expr() : lhs_(LHS()) {} 
      
      explicit ct_unary_expr(internal_lhs_type lhs) : lhs_(lhs){}
                          
      internal_lhs_type lhs() const { return lhs_; }
      
      template <typename VectorType>
      numeric_type operator()(VectorType const & v) const
      {
        //std::cout << "ct_expr::operator()" << std::endl;
        return OP::apply(static_cast<numeric_type>(lhs_(v)), static_cast<numeric_type>(rhs_(v)));
      }
      
    private:
      internal_lhs_type lhs_;
  };
  
  
  //stream operator for output:
  template <typename LHS, typename OP>
  std::ostream& operator<<(std::ostream & stream, ct_unary_expr<LHS, OP> const & other)
  {
    stream << "[" << other.lhs() << OP().str() << "]";
    return stream;
  }

  
}

#endif