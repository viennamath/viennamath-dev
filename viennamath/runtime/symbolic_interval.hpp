/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_RUNTIME_SYMBOLIC_INTERVAL_HPP
#define VIENNAMATH_RUNTIME_SYMBOLIC_INTERVAL_HPP

#include <ostream>
#include "viennamath/forwards.h"

namespace viennamath
{
  
  /** @brief A symbolic runtime interval */
  template <typename InterfaceType>
  class rt_symbolic_interval
  {

    public:
      typedef rt_expr<InterfaceType>                  value_type;
      typedef InterfaceType                           interface_type;
      typedef typename InterfaceType::numeric_type    numeric_type;
      
      rt_symbolic_interval(id_type interval_id = 0) : id_(interval_id) {}
      
      id_type id() const { return id_; }
      
    private:
      id_type id_;      
  };

  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, rt_symbolic_interval<InterfaceType> const & e)
  {
    stream << "symbolic_interval[" << e.id() << "]";
    return stream;
  }
  
  
  
  
  //////// helper functions for creating equations (uniform interface for compile time and run time: ///////////
  
 

  
}

#endif