/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CONSTANT_HPP
#define VIENNAMATH_CONSTANT_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
//#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  //per default, we assume floating point constants, which cannot be tackled with template arguments
  template <typename ScalarType>
  class constant : public expression_interface
  {
      typedef constant<ScalarType>     self_type;
    public:
      explicit constant(ScalarType s_) : s(s_) {};

      self_type operator() () const
      {
        return *this;
      }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const
      {
        return *this;
      }
      
      operator ScalarType() const { return s; }
      
      //interface requirements:
      expression_interface * clone() const { return new constant<ScalarType>(s); }
      numeric_type eval(std::vector<double> const & v) const { return s; }
      numeric_type eval(numeric_type v) const { return s; }
      bool is_constant() const { return true; }
      std::string str() const
      {
        std::stringstream ss;
        ss << "constant(" << s << ")";
        return ss.str();      
      }
      numeric_type unwrap() const { return s; }
      
      expression_interface * substitute(const expr & e,
                                        const expr & repl) const
      {
        return clone();
      };    
      
      bool equal(const expression_interface * other) const
      {
        return dynamic_cast< const constant<ScalarType> *>(other) != NULL;
      }
      
      expression_interface * diff(const expr & diff_var) const
      {
        return new constant<ScalarType>(0);
      }
      
    private:
      ScalarType s;
  };

  
}

#endif