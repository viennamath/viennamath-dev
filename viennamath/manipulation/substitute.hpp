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
  template <unsigned long id, typename InterfaceType, typename ReplacementType, typename ExpressionType>
  expr<InterfaceType> substitute(variable<id, InterfaceType> const & u,
                                 ReplacementType const & repl,
                                 ExpressionType const & e)
  {
    expr<InterfaceType> temp(e.substitute(&u, &repl));
    return expr<InterfaceType>(temp.get()->optimize());
  }

  /** @brief Replaces all occurances of the variable u in the expression 'e' with 'u'. */
  template <unsigned long id, typename InterfaceType, typename ReplacementType>
  expr<InterfaceType> substitute(variable<id, InterfaceType> const & u,
                                 ReplacementType const & repl,
                                 expr<InterfaceType> const & e)
  {
    expr<InterfaceType> temp(e.get()->substitute(&u, &repl));
    return expr<InterfaceType>(temp.get()->optimize());
  }




  //substitute binary_expressions (for fem):
  template <typename InterfaceType, typename ReplacementType>
  expr<InterfaceType> substitute(unary_expr<InterfaceType> const & search,
                                 ReplacementType const & repl,
                                 expr<InterfaceType> const & e)
  {
    expr<InterfaceType> temp(e.get()->substitute(&search, &repl));
    return expr<InterfaceType>(temp.get()->optimize());
  }

  template <typename InterfaceType>
  expr<InterfaceType> substitute(unary_expr<InterfaceType> const & search,
                                 expr<InterfaceType> const & repl,
                                 expr<InterfaceType> const & e)
  {
    expr<InterfaceType> temp(e.get()->substitute(&search, repl.get()));
    return expr<InterfaceType>(temp.get()->optimize());
  }

  template <typename InterfaceType, typename ReplacementType>
  expr<InterfaceType> substitute(binary_expr<InterfaceType> const & search,
                                 ReplacementType const & repl,
                                 expr<InterfaceType> const & e)
  {
    expr<InterfaceType> temp(e.get()->substitute(&search, &repl));
    return expr<InterfaceType>(temp.get()->optimize());
  }

  template <typename InterfaceType>
  expr<InterfaceType> substitute(expr<InterfaceType> const & search,
                                 expr<InterfaceType> const & repl,
                                 expr<InterfaceType> const & e)
  {
    expr<InterfaceType> temp(e.get()->substitute(search.get(), repl.get()));
    return expr<InterfaceType>(temp.get()->optimize());
  }

}

#endif