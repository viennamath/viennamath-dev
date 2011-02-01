/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_APPLY_COORDINATE_SYSTEM_HPP
#define VIENNAMATH_APPLY_COORDINATE_SYSTEM_HPP

#include "viennamath/forwards.h"
#include "viennamath/op_tags.hpp"
#include "viennamath/unknown_func.hpp"
#include "viennamath/integral.hpp"
#include "viennamath/substitute.hpp"
#include "viennamath/diff.hpp"
#include "viennamath/equation.hpp"

namespace viennamath
{
  template <unsigned long dim>
  struct cartesian {};
  
  
  //TODO: compile time derivation
  


  //tries to automatically derive the weak formulation from the strong formulation
  equation apply_coordinate_system(cartesian<1>,
                                   equation const & equ)
  {
    unknown_func<0> u;
    test_func<0> v;
    variable<0> x;
    
    //TODO: More general applications -> requires vector of expressions
    expr new_lhs(substitute( grad(u) * grad(v),
                             diff(u, x) * diff(v, x),
                             equ.lhs()
                           )
                );
    return equation( new_lhs,
                     equ.rhs()
                   );
  }


  equation apply_coordinate_system(cartesian<2>,
                                   equation const & equ)
  {
    unknown_func<0> u;
    test_func<0> v;
    variable<0> x;
    variable<1> y;
    
    //TODO: More general applications -> requires vector of expressions
    expr new_lhs(substitute( grad(u) * grad(v),
                             diff(u, x) * diff(v, x) + diff(u, y) * diff(v, y),
                             equ.lhs()
                           )
                );
    return equation( new_lhs,
                     equ.rhs()
                   );
  }

  equation apply_coordinate_system(cartesian<3>,
                                   equation const & equ)
  {
    unknown_func<0> u;
    test_func<0> v;
    variable<0> x;
    variable<1> y;
    variable<2> z;
    
    //TODO: More general applications -> requires vector of expressions
    expr new_lhs(substitute( grad(u) * grad(v),
                             diff(u, x) * diff(v, x) + diff(u, y) * diff(v, y) + diff(u, z) * diff(v, z),
                             equ.lhs()
                           )
                );
    return equation( new_lhs,
                     equ.rhs()
                   );
  }

}

#endif