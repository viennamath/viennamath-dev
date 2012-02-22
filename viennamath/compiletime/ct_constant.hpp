#ifndef VIENNAMATH_COMPILETIME_CT_CONSTANT_HPP
#define VIENNAMATH_COMPILETIME_CT_CONSTANT_HPP

/* =======================================================================
   Copyright (c) 2012, Institute for Microelectronics,
                       Institute for Analysis and Scientific Computing,
                       TU Wien.
                             -----------------
               ViennaMath - Symbolic and Numerical Math in C++
                             -----------------

   Author:     Karl Rupp                          rupp@iue.tuwien.ac.at

   License:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */




#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  //A compile time constant using C++ template magic :-)
  template <long value_>
  class ct_constant
  {    
      typedef ct_constant<value_>     self_type;
    public:
      explicit ct_constant() {};
      
      self_type operator() () const { return *this; }

      template <typename VectorType>
      self_type operator() (const VectorType & p) const { return *this; }
      
      operator long() const { return value_; }
      
      std::string str() const
      {
        std::stringstream ss;
        ss << "ct_constant<" << value_ << ">";
        return ss.str();      
      }
      
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