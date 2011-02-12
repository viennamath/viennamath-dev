/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_FUNCTION_SYMBOL_HPP
#define VIENNAMATH_FUNCTION_SYMBOL_HPP

#include <ostream>
#include <sstream>
#include "viennamath/forwards.h"
#include "viennamath/expression_compile_time.hpp"
//#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  /////// two common tags:
  
  //tag for an unknown function:
  template <unsigned long id>
  struct unknown_tag
  {
    static std::string str()
    {
      std::stringstream ss;
      ss << "unknown[" << id << "]";
      return ss.str();
    }
  };
    
  //tag for test function:
  template <unsigned long id>
  struct test_tag
  {
    static std::string str()
    {
      std::stringstream ss;
      ss << "test[" << id << "]";
      return ss.str();
    }
  };
  
  
  
  
  
  

  /** @brief A function symbol. Can be used for unknown functions, test functions, etc. Cannot be evaluated, but substituted with an evaluable object 
   *
   * @tparam Tag    A tag class that is typically used to distinguish between different function symbols. Tag requirements: 'static std::string str();' which returns an identification string
   */
  template <typename Tag>
  class function_symbol : public expression_interface
  {
      typedef function_symbol<Tag>     self_type;
    public:
      explicit function_symbol() {};

      //interface requirements:
      expression_interface * clone() const { return new self_type(); }
      numeric_type eval(std::vector<double> const & v) const { throw "Cannot evaluate unknown_func!"; return 0; }
      numeric_type eval(numeric_type v) const { throw "Cannot evaluate unknown_func!"; return 0; }
      std::string str() const
      {
        std::stringstream ss;
        ss << "function_symbol<" << Tag::str() << ">";
        return ss.str();      
      }
      numeric_type unwrap() const { throw "Cannot evaluate unknown_func to a number!"; }
      
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
        //this code should not be reached, because function_symbol is symbolically differentiated at a higher level
        throw "Cannot differentiate unknown_func!";
        return NULL;
      }
  };

  
}

#endif