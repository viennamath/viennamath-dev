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

namespace viennamath
{
  
  
  //TODO: compile time substitution
  
  
  
  
  
  //public interface:
  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <unsigned long id, typename ReplacementType, typename ExpressionType>
  expr substitute(variable<id> const & u,
                  ReplacementType const & repl,
                  ExpressionType const & e)
  {
    expr temp(e.substitute(expr(u), repl));
    return expr(temp.get()->optimize());
  }

  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <unsigned long id, typename ReplacementType>
  expr substitute(variable<id> const & u,
                  ReplacementType const & repl,
                  expr const & e)
  {
    expr temp(e.get()->substitute(expr(u), repl));
    return expr(temp.get()->optimize());
  }




  //substitute binary_expressions (for fem):
  template <typename ReplacementType>
  expr substitute(expr const & search,
                  ReplacementType const & repl,
                  expr const & e)
  {
    expr temp(e.get()->substitute(expr(search), repl));
    return expr(temp.get()->optimize());
  }

}

#endif