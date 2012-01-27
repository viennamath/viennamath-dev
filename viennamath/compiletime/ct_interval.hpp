/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_INTERVAL_HPP
#define VIENNAMATH_CT_INTERVAL_HPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  /** @brief A compile time interval */
  template <typename LHS, typename RHS>
  class ct_interval {};
  
  template <typename LHS, typename RHS>
  std::ostream& operator<<(std::ostream & stream, ct_interval<LHS, RHS> const & u)
  {
    stream << "ct_interval(" << LHS() << ", " << RHS() << ")";
    return stream;
  }

  
  //
  // compile time 
  // [expression, ct_constant, variable] for each argument -> 9 overloads
  //
  
  
  //first argument: expression
  template <typename LHS1, typename OP1, typename RHS1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_expr<LHS1, OP1, RHS1>,
              ct_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_expr<LHS1, OP1, RHS1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_expr<LHS1, OP1, RHS1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <typename LHS1, typename OP1, typename RHS1,
            long value>
  ct_interval<ct_expr<LHS1, OP1, RHS1>,
              ct_constant<value> > 
  make_interval(ct_expr<LHS1, OP1, RHS1> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_interval<ct_expr<LHS1, OP1, RHS1>,
                       ct_constant<value> >(); 
  }

  template <typename LHS1, typename OP1, typename RHS1,
            unsigned long id>
  ct_interval<ct_expr<LHS1, OP1, RHS1>,
              ct_variable<id> > 
  make_interval(ct_expr<LHS1, OP1, RHS1> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_expr<LHS1, OP1, RHS1>,
                       ct_variable<id> >(); 
  }




  //first argument: ct_constant
  template <long value1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_constant<value1>,
              ct_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <long value1,
            long value2>
  ct_interval<ct_constant<value1>,
              ct_constant<value2> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_constant<value2> >(); 
  }

  template <long value1,
            unsigned long id>
  ct_interval<ct_constant<value1>,
              ct_variable<id> > 
  make_interval(ct_constant<value1> const & lhs,
                ct_variable<id> const & rhs)
  {
    return ct_interval<ct_constant<value1>,
                       ct_variable<id> >(); 
  }

  
  //first argument: variable
  template <unsigned long id1,
            typename LHS2, typename OP2, typename RHS2>
  ct_interval<ct_variable<id1>,
              ct_expr<LHS2, OP2, RHS2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <unsigned long id1,
            long value2>
  ct_interval<ct_variable<id1>,
              ct_constant<value2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_constant<value2> >(); 
  }

  template <unsigned long id1,
            unsigned long id2>
  ct_interval<ct_variable<id1>,
              ct_variable<id2> > 
  make_interval(ct_variable<id1> const & lhs,
                ct_variable<id2> const & rhs)
  {
    return ct_interval<ct_variable<id1>,
                       ct_variable<id2> >(); 
  }
  
}

#endif