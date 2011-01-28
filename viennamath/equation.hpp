/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EQUATION_CPP
#define VIENNAMATH_EQUATION_CPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  /** @brief A compile time equation */
  template <typename LHS, typename RHS>
  class ct_equation
  {
    
    
  };
  
  template <typename LHS, typename RHS>
  std::ostream& operator<<(std::ostream & stream, ct_equation<LHS, RHS> const & u)
  {
    stream << "ct_equation(" << LHS() << " = " << RHS() << ")";
    return stream;
  }
  
  
  
  /** @brief A runtime equation */
  class equation
  {

    public:
      equation() {};
      
      equation(const expr & lhs,
               const expr & rhs) : lhs_(lhs.get()->clone()), rhs_(rhs.get()->clone()) {}
      
      expr const & lhs() const { return lhs_; }
      expr const & rhs() const { return rhs_; }
      
    private:
      expr lhs_;
      expr rhs_;
  };

  std::ostream& operator<<(std::ostream & stream, equation const & e)
  {
    stream << "equation(" << e.lhs() << " = " << e.rhs() << ")";
    return stream;
  }
  
  
  
  
  //////// helper functions for creating equations (uniform interface for compile time and run time: ///////////
  
  
  //
  // run time
  //
  equation make_equation(expr const & lhs, expr const & rhs)
  {
    return equation(lhs, rhs); 
  }
  
  equation make_equation(expr const & lhs, numeric_type_proxy const & rhs)
  {
    return equation(lhs, rhs); 
  }
  
  equation make_equation(numeric_type_proxy const & lhs, expr const & rhs)
  {
    return equation(lhs, rhs); 
  }
  
  
  //
  // compile time 
  // [expression, ct_constant, variable] for each argument -> 9 overloads
  //
  
  
  //first argument: expression
  template <typename LHS1, typename OP1, typename RHS1,
            typename LHS2, typename OP2, typename RHS2>
  ct_equation<expression<LHS1, OP1, RHS1>,
              expression<LHS2, OP2, RHS2> > 
  make_equation(expression<LHS1, OP1, RHS1> const & lhs,
                expression<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<expression<LHS1, OP1, RHS1>,
                       expression<LHS2, OP2, RHS2> >(); 
  }
  
  template <typename LHS1, typename OP1, typename RHS1,
            long value>
  ct_equation<expression<LHS1, OP1, RHS1>,
              ct_constant<value> > 
  make_equation(expression<LHS1, OP1, RHS1> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_equation<expression<LHS1, OP1, RHS1>,
                       ct_constant<value> >(); 
  }

  template <typename LHS1, typename OP1, typename RHS1,
            unsigned long id>
  ct_equation<expression<LHS1, OP1, RHS1>,
              variable<id> > 
  make_equation(expression<LHS1, OP1, RHS1> const & lhs,
                variable<id> const & rhs)
  {
    return ct_equation<expression<LHS1, OP1, RHS1>,
                       variable<id> >(); 
  }




  //first argument: ct_constant
  template <long value1,
            typename LHS2, typename OP2, typename RHS2>
  ct_equation<ct_constant<value1>,
              expression<LHS2, OP2, RHS2> > 
  make_equation(ct_constant<value1> const & lhs,
                expression<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<ct_constant<value1>,
                       expression<LHS2, OP2, RHS2> >(); 
  }
  
  template <long value1,
            long value2>
  ct_equation<ct_constant<value1>,
              ct_constant<value2> > 
  make_equation(ct_constant<value1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_equation<ct_constant<value1>,
                       ct_constant<value2> >(); 
  }

  template <long value1,
            unsigned long id>
  ct_equation<ct_constant<value1>,
              variable<id> > 
  make_equation(ct_constant<value1> const & lhs,
                variable<id> const & rhs)
  {
    return ct_equation<ct_constant<value1>,
                       variable<id> >(); 
  }

  
  //first argument: variable
  template <unsigned long id1,
            typename LHS2, typename OP2, typename RHS2>
  ct_equation<variable<id1>,
              expression<LHS2, OP2, RHS2> > 
  make_equation(variable<id1> const & lhs,
                expression<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<variable<id1>,
                       expression<LHS2, OP2, RHS2> >(); 
  }
  
  template <unsigned long id1,
            long value2>
  ct_equation<variable<id1>,
              ct_constant<value2> > 
  make_equation(variable<id1> const & lhs,
                ct_constant<value2> const & rhs)
  {
    return ct_equation<variable<id1>,
                       ct_constant<value2> >(); 
  }

  template <unsigned long id1,
            unsigned long id2>
  ct_equation<variable<id1>,
              variable<id2> > 
  make_equation(variable<id1> const & lhs,
                variable<id2> const & rhs)
  {
    return ct_equation<variable<id1>,
                       variable<id2> >(); 
  }
  
}

#endif