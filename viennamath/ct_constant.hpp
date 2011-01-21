/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_CONSTANT_HPP
#define VIENNAMATH_CT_CONSTANT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  //A compile time constant using C++ template magic :-)
  template <long value_>
  class ct_constant : public expression_interface
  {    
      typedef ct_constant<value_>     self_type;
    public:
      explicit ct_constant() {};
      
      self_type operator() () const { return *this; }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const { return *this; }
      
      operator long() const { return value_; }
      
      //interface requirements:
      expression_interface * clone() const { return new ct_constant<value_>(); }
      numeric_type eval(std::vector<double> const & v) const { return value_; }
      numeric_type eval(numeric_type v) const { return value_; }
      bool is_constant() const { return true; }
      std::string str() const
      {
        std::stringstream ss;
        ss << "ct_constant<" << value_ << ">";
        return ss.str();      
      }
      numeric_type unwrap() const { return value_; }
      
      virtual expression_interface * substitute(const expression_interface * e,
                                                const expression_interface * repl) const
      {
        return clone();
      };    
      
  };

  template <long value_>
  std::ostream& operator<<(std::ostream & stream,
                           ct_constant<value_> const & c)
  {
    stream << c.str();
    return stream;
  }
  
  
  
  
  
}

#endif