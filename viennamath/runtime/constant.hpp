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
//#include "viennamath/expression_compile_time.hpp"
#include "viennamath/runtime/expression_interface.hpp"
//#include "viennamath/expression_run_time.hpp"

namespace viennamath
{
  
  //per default, we assume floating point constants, which cannot be tackled with template arguments
  template <typename ScalarType, /* see forwards.h for default argument */
            typename InterfaceType /* see forwards.h for default argument */>
  class constant : public InterfaceType
  {
      typedef constant<ScalarType, InterfaceType>     self_type;
    public:
      typedef typename InterfaceType::numeric_type    numeric_type;
      
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
      InterfaceType * clone() const { return new constant<ScalarType>(s); }
      numeric_type eval(std::vector<numeric_type> const & v) const { return s; }
      numeric_type eval(numeric_type v) const { return s; }
      bool is_constant() const { return true; }
      std::string str() const
      {
        std::stringstream ss;
        ss << "constant(" << s << ")";
        return ss.str();      
      }
      numeric_type unwrap() const { return s; }
      
      InterfaceType * substitute(const InterfaceType * e,
                                 const InterfaceType * repl) const
      {
        return clone();
      };    
      
      bool equal(const InterfaceType * other) const
      {
        return dynamic_cast< const self_type *>(other) != NULL;
      }
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        return new constant<ScalarType>(0);
      }
      
    private:
      ScalarType s;
  };

  
}

#endif