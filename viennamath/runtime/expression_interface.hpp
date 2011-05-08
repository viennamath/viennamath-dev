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
#include "viennamath/runtime/functor_wrapper.hpp"

namespace viennamath
{
  
  //class expression_interface;
  //interface for runtime dispatches:
  template <typename NumericT>
  class expression_interface
  {
    public:
      typedef NumericT                          numeric_type;
      typedef expression_interface<NumericT>    interface_type;
      
      virtual ~expression_interface() {}
      
      virtual interface_type * clone() const = 0;  //receiver owns pointer!
      virtual std::string deep_str() const = 0;
      virtual std::string shallow_str() const { return this->deep_str(); }
      virtual NumericT eval(std::vector<NumericT> const & v) const = 0;
      virtual NumericT eval(NumericT val) const = 0;
      
      virtual bool is_unary() const { return true; }
      
      /** @brief Returns true, if the expression can be evaluated without providing values for variables (i.e. the expression is a constant) */
      virtual bool is_constant() const { return false; }

      /** @brief Returns the numeric value of the expression. */
      virtual NumericT unwrap() const = 0;
      
      /** @brief Checks the current expression for being equal to 'other'. Checks for same type only, does not check members. */
      virtual bool shallow_equal(const interface_type * other) const = 0;
      
      /** @brief Checks the current expression for being equal to 'other'. Performs a deep check for equality of members. */
      virtual bool deep_equal(const interface_type * other) const = 0;

      virtual interface_type * recursive_manipulation(manipulation_wrapper<interface_type> const & fw) const { return fw(this); }   
      virtual void recursive_traversal(traversal_wrapper<interface_type> const & fw) const { fw(this); }   

      ////// Deprecated section: ////////////////
      
      /** @brief Substitutes repl if the current expression equals e */
      virtual interface_type * substitute(const interface_type * e,
                                                const interface_type * repl) const = 0;  //receiver owns pointer! Function parameters must not be manipulated!
      virtual interface_type * optimize() const { return clone(); }  //receiver owns pointer!
      virtual bool optimizable() const { return false; }      
      virtual interface_type * diff(const interface_type * diff_var) const = 0;   //receiver owns pointer! Function parameter diff_var not be manipulated!
         
         
  };
 
  

  
}

#endif