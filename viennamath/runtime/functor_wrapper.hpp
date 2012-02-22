#ifndef VIENNAMATH_RUNTIME_FUNCTOR_WRAPPER_HPP
#define VIENNAMATH_RUNTIME_FUNCTOR_WRAPPER_HPP

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
#include <sstream>
#include "viennamath/forwards.h"

namespace viennamath
{
  template <typename InterfaceType /* see forwards.h for default argument */>
  class rt_manipulation_interface
  {
    public:
      virtual InterfaceType * operator()(InterfaceType const * e) const { return e->clone(); };
      virtual bool modifies(InterfaceType const * e) const { return false; }
  };

  /** @brief: Type erasure for functors acting on expressions */
  
  template <typename InterfaceType /* default argument in forwards.h */>
  class rt_manipulation_wrapper
  {
    public:
      template <typename T>
      rt_manipulation_wrapper(T const * t) : functor_(t) {}
      
      InterfaceType * operator()(InterfaceType const * e) const
      {
        return functor_.get()->operator()(e); 
      }

      bool modifies(InterfaceType const * e) const { return functor_->modifies(e); }

    private:
      std::auto_ptr< const rt_manipulation_interface<InterfaceType> > functor_;
  };

  
  template <typename InterfaceType /* see forwards.h for default argument */>
  class rt_traversal_interface
  {
    public:
      virtual void operator()(InterfaceType const * e) const = 0;
      virtual bool step_into(InterfaceType const * e) const { return true; }
  };
  
  template <typename InterfaceType /* default argument in forwards.h */>
  class rt_traversal_wrapper
  {
    public:
      template <typename T>
      rt_traversal_wrapper(T const * t) : functor_(t) {}
      
      void operator()(InterfaceType const * e) const
      {
        functor_.get()->operator()(e); 
      }

      bool step_into(InterfaceType const * e) const { return functor_.get()->step_into(e); }

    private:
      std::auto_ptr< const rt_traversal_interface<InterfaceType> > functor_;
  };

  
  template <typename CastToType>
  struct callback_if_castable
  {
    template <typename InterfaceType, typename FunctorType>
    static bool apply(InterfaceType const * e, FunctorType const & functor)
    {
      CastToType const * ptr = dynamic_cast< CastToType const *>(e);
      if (ptr != NULL)
      {
        functor(*ptr);
        return true;
      }
      return false;
    }
    
  };
  
    
}

#endif