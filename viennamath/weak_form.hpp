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
#include "viennamath/op_tags.hpp"
#include "viennamath/unknown_func.hpp"
#include "viennamath/integral.hpp"
#include "viennamath/substitute.hpp"
#include "viennamath/equation.hpp"

namespace viennamath
{
  
  
  //TODO: compile time derivation
  


  //tries to automatically derive the weak formulation from the strong formulation
  equation weak_form(equation const & strong_formulation)
  {
    //TODO: More general derivations: Transform div(expr) to expr * grad(v)
    expr new_lhs(substitute( laplace(unknown_func<0>()),
                             constant<double>(-1) * (grad(unknown_func<0>()) * grad(test_func<0>())),
                             strong_formulation.lhs()
                           )
                );
    return equation( integral(Omega(), new_lhs, symbolic_tag()),
                     integral(Omega(), strong_formulation.rhs() * test_func<0>(), symbolic_tag())
                   );
  }

}

#endif