/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_CT_FUNCTION_SYMBOL_HPP
#define VIENNAMATH_CT_FUNCTION_SYMBOL_HPP

#include <ostream>
#include <sstream>
#include <vector>
#include "viennamath/forwards.h"
//#include "viennamath/expression_compile_time.hpp"
//#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  /////// two common tags:
  
  //tag for an unknown function:
  template <id_type ct_id = 0>
  struct unknown_tag
  {
    static std::string str()
    {
      std::stringstream ss;
      ss << "unknown[" << ct_id << "]";
      return ss.str();
    }
    
    static id_type tag_id() { return 0; }
  };
    
  //tag for test function:
  template <id_type ct_id = 0>
  struct test_tag
  {
    static std::string str()
    {
      std::stringstream ss;
      ss << "test[" << ct_id << "]";
      return ss.str();
    }
    
    static id_type tag_id() { return 1; }
  };
  
  
  
  
  
  

  /** @brief A function symbol. Can be used for unknown functions, test functions, etc. Cannot be evaluated, but substituted with an evaluable object 
   *
   * @tparam Tag    A tag class that is typically used to distinguish between different function symbols. Tag requirements: 'static std::string str();' which returns an identification string
   */
  template <typename Tag>
  class ct_function_symbol
  {
      static std::string str()
      {
        return Tag::str();
      }
  };

  
  
  template <typename Tag>
  std::ostream& operator<<(std::ostream & stream, ct_function_symbol<Tag> const & v)
  {
    stream << ct_function_symbol<Tag>::str();
    return stream;
  }
  
  
  
}

#endif