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
  template <typename InterfaceType>
  class equation
  {

    public:
      equation() {};
      
      
      equation(const expr<InterfaceType> & lhs,
               const expr<InterfaceType> & rhs) : lhs_(lhs.get()->clone()), rhs_(rhs.get()->clone()) {}
      
      expr<InterfaceType> const & lhs() const { return lhs_; }
      expr<InterfaceType> const & rhs() const { return rhs_; }
      
    private:
      expr<InterfaceType> lhs_;
      expr<InterfaceType> rhs_;
  };

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, equation<InterfaceType> const & e)
  {
    stream << "equation(" << e.lhs() << " = " << e.rhs() << ")";
    return stream;
  }
  
  
  
  
  //////// helper functions for creating equations (uniform interface for compile time and run time: ///////////
  
  
  //
  // run time
  //
  
  ////// scalar is first argument:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, constant<NumericT, InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }
  
  template <unsigned long id, typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, variable<id, InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }
  
  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, unary_expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, binary_expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  template <typename InterfaceType>
  equation<InterfaceType> make_equation(typename InterfaceType::numeric_type lhs, expr<InterfaceType> const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  
  //constant:
  template <typename NumericT, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(constant<NumericT, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //variable:
  template <unsigned long id, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(variable<id, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //function_symbol:
  template <typename T, typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(function_symbol<T, InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //unary:
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(unary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }


  //binary
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(binary_expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //expr
  template <typename InterfaceType, typename RHSType>
  equation<InterfaceType> make_equation(expr<InterfaceType> const & lhs, RHSType const & rhs)
  {
    return equation<InterfaceType>(lhs, rhs); 
  }

  //compile time with run time stuff also possible:
  template <typename LHS, typename OP, typename RHS, typename RHSType>
  equation<> make_equation(ct_expr<LHS, OP, RHS> const & lhs, RHSType const & rhs)
  {
    return equation<>(lhs, rhs); 
  }




  //
  // compile time 
  // [expression, ct_constant, variable] for each argument -> 9 overloads
  //
  
  
  //first argument: expression
  template <typename LHS1, typename OP1, typename RHS1,
            typename LHS2, typename OP2, typename RHS2>
  ct_equation<ct_expr<LHS1, OP1, RHS1>,
              ct_expr<LHS2, OP2, RHS2> > 
  make_equation(ct_expr<LHS1, OP1, RHS1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<ct_expr<LHS1, OP1, RHS1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
  }
  
  template <typename LHS1, typename OP1, typename RHS1,
            long value>
  ct_equation<ct_expr<LHS1, OP1, RHS1>,
              ct_constant<value> > 
  make_equation(ct_expr<LHS1, OP1, RHS1> const & lhs,
                ct_constant<value> const & rhs)
  {
    return ct_equation<ct_expr<LHS1, OP1, RHS1>,
                       ct_constant<value> >(); 
  }

  template <typename LHS1, typename OP1, typename RHS1,
            unsigned long id>
  ct_equation<ct_expr<LHS1, OP1, RHS1>,
              variable<id> > 
  make_equation(ct_expr<LHS1, OP1, RHS1> const & lhs,
                variable<id> const & rhs)
  {
    return ct_equation<ct_expr<LHS1, OP1, RHS1>,
                       variable<id> >(); 
  }




  //first argument: ct_constant
  template <long value1,
            typename LHS2, typename OP2, typename RHS2>
  ct_equation<ct_constant<value1>,
              ct_expr<LHS2, OP2, RHS2> > 
  make_equation(ct_constant<value1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<ct_constant<value1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
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
              ct_expr<LHS2, OP2, RHS2> > 
  make_equation(variable<id1> const & lhs,
                ct_expr<LHS2, OP2, RHS2> const & rhs)
  {
    return ct_equation<variable<id1>,
                       ct_expr<LHS2, OP2, RHS2> >(); 
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