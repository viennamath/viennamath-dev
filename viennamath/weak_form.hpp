/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_WEAK_FORM_HPP
#define VIENNAMATH_WEAK_FORM_HPP

#include "viennamath/forwards.h"
#include "viennamath/compiletime/unary_op_tags.hpp"
#include "viennamath/runtime/unary_operators.hpp"
#include "viennamath/manipulation/unary_operators_manipulation.hpp"
#include "viennamath/manipulation/integral.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/runtime/equation.hpp"
#include "viennamath/runtime/function_symbol.hpp"

namespace viennamath
{
  //TODO: Is this the right place for the derivation of a weak formulation? Shouldn't this go into ViennaFEM or ViennaFVM?
  
  
  //TODO: compile time derivation
  


  //tries to automatically derive the weak formulation from the strong formulation
  template <typename InterfaceType>
  equation<InterfaceType> make_weak_form(equation<InterfaceType> const & strong_formulation)
  {
    //TODO: More general derivations: Transform div(expr) to expr * grad(v)
    expr<InterfaceType> new_lhs(substitute( laplace(function_symbol<InterfaceType>(0, unknown_tag<0>())),
                                            constant<typename InterfaceType::numeric_type, InterfaceType>(-1) * (grad(function_symbol<InterfaceType>(0, unknown_tag<0>())) * grad(function_symbol<InterfaceType>(0, test_tag<0>()))),
                                            strong_formulation.lhs()
                                          )
                               );
    return equation<InterfaceType>( integral(Omega(), new_lhs, symbolic_tag()),
                                    integral(Omega(), strong_formulation.rhs() * function_symbol<InterfaceType>(0, test_tag<0>()), symbolic_tag())
                                  );
  }

}

#endif