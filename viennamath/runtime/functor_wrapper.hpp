/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_FUNCTOR_WRAPPER_HPP
#define VIENNAMATH_FUNCTOR_WRAPPER_HPP

#include <ostream>
#include <sstream>
#include "viennamath/forwards.h"

namespace viennamath
{
  template <typename InterfaceType /* see forwards.h for default argument */>
  class functor_interface
  {
    public:
      /** @brief Copy data from one object to another */
      virtual InterfaceType * apply(InterfaceType const * e) const = 0;
  };
  
  
  /** @brief: Type erasure for functors acting on expressions */
  
  template <typename InterfaceType /* default argument in forwards.h */>
  class functor_wrapper
  {
    public:
      template <typename T>
      functor_wrapper(T const * t) : functor_(t) {}
      
      InterfaceType * operator()(InterfaceType const * e) const
      {
        return functor_.get()->apply(e); 
      }

    private:
      std::auto_ptr< const functor_interface<InterfaceType> > functor_;
  };


}

#endif