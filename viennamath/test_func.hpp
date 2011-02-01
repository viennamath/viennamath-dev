/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_TEST_FUNC_HPP
#define VIENNAMATH_TEST_FUNC_HPP

#include <ostream>
#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
//#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  //per default, we assume floating point constants, which cannot be tackled with template arguments
  template <unsigned long id>
  class test_func : public expression_interface
  {
      typedef test_func<id>     self_type;
    public:
      explicit test_func() {};

      //interface requirements:
      expression_interface * clone() const { return new self_type(); }
      numeric_type eval(std::vector<double> const & v) const { throw "Cannot evaluate unknown_func!"; return 0; }
      numeric_type eval(numeric_type v) const { throw "Cannot evaluate unknown_func!"; return 0; }
      std::string str() const
      {
        std::stringstream ss;
        ss << "test_func<" << id << ">";
        return ss.str();      
      }
      numeric_type unwrap() const { throw "Cannot evaluate unknown_func!"; }
      
      expression_interface * substitute(const expr & e,
                                        const expr & repl) const
      {
        if (dynamic_cast<const self_type *>(e.get()) != NULL)
          return repl.get()->clone();
        return clone();
      };    
      
      bool equal(const expression_interface * other) const
      {
        return dynamic_cast< const self_type *>(other) != NULL;
      }
      
      expression_interface * diff(const expr & diff_var) const
      {
        throw "Cannot differentiate unknown_func!";
        return NULL;
      }
  };

  
}

#endif