/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_INTERFACE_HPP
#define VIENNAMATH_EXPRESSION_INTERFACE_HPP

#include <vector>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  //class expression_interface;
  //interface for runtime dispatches:
  template <typename NumericT>
  class expression_interface
  {
    public:
      typedef NumericT         numeric_type;
      
      virtual ~expression_interface() {}
      
      virtual expression_interface * clone() const = 0;  //receiver owns pointer!
      virtual std::string str() const = 0;
      virtual NumericT eval(std::vector<NumericT> const & v) const = 0;
      virtual NumericT eval(NumericT val) const = 0;
      virtual expression_interface * optimize() const { return clone(); }  //receiver owns pointer!
      virtual bool optimizable() const { return false; }      
      
      virtual bool is_unary() const { return true; }
      
      /** @brief Returns true, if the expression can be evaluated without providing values for variables (i.e. the expression is a constant) */
      virtual bool is_constant() const { return false; }
      
      virtual NumericT unwrap() const = 0;
      virtual expression_interface * substitute(const expression_interface * e,
                                                const expression_interface * repl) const = 0;  //receiver owns pointer! Function parameters must not be manipulated!
                                                
      virtual bool equal(const expression_interface * other) const = 0;
      
      virtual const expression_interface               * lhs() const { return this; };
      //virtual const op_interface<expression_interface> *          op() const { return NULL; }  //primitives do not have an operator   //TODO: This is a showstopper! Provide something better here!
      //virtual const expression_interface               * rhs() const { return NULL; } //unary expressions do not have a right-hand side


      virtual expression_interface * diff(const expression_interface * diff_var) const = 0;   //receiver owns pointer! Function parameter diff_var not be manipulated!
  };
 
  

  
}

#endif