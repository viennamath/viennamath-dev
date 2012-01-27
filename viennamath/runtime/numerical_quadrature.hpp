/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_RUNTIME_NUMERICAL_QUADRATURE_HPP
#define VIENNAMATH_RUNTIME_NUMERICAL_QUADRATURE_HPP

#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <sstream>
#include "viennamath/forwards.h"
#include "viennamath/runtime/rt_integral.hpp"

namespace viennamath
{
  
  template <typename InterfaceType>
  class numerical_quadrature_interface
  {
    public:
      typedef typename InterfaceType::numeric_type   numeric_type;
      
      virtual rt_expr<InterfaceType> eval(rt_interval<InterfaceType> const & interv,
                                          rt_expr<InterfaceType> const & e,
                                          rt_variable<InterfaceType> const & var) const = 0;
  };
  
  
  template <typename InterfaceType = default_interface_type>
  struct rt_gauss_quad_1 : public numerical_quadrature_interface<InterfaceType>
  {
    enum { id = 1 };
    
    rt_expr<InterfaceType> eval(rt_interval<InterfaceType> const & interv,
                                rt_expr<InterfaceType> const & e,
                                rt_variable<InterfaceType> const & var) const
    {
      rt_expr<InterfaceType> tmp = viennamath::substitute(var, (interv.lower() + interv.upper()) / 2.0, e);
      return tmp * (interv.upper() - interv.lower());
    }
  };
  typedef rt_gauss_quad_1<>      gauss_quad_1;
  
  
  

  
  
  template <typename InterfaceType = default_interface_type>
  class rt_numerical_quadrature 
  {
    public:
      rt_numerical_quadrature(unsigned long id)
      {
        if (id == 1)
          quadrature_rule_ = std::auto_ptr<numerical_quadrature_interface<InterfaceType> >(new rt_gauss_quad_1<InterfaceType>());
        else
          throw "Not supported!";
      }
      
      
      rt_expr<InterfaceType> operator()(rt_expr<InterfaceType> const & e) const
      {
        
        if (dynamic_cast<const rt_unary_expr<InterfaceType> *>(e.get()) != NULL)
        {
          typedef op_unary<op_rt_integral<InterfaceType>, InterfaceType>    IntegrationOperation;
          
          const rt_unary_expr<InterfaceType> * integrand = dynamic_cast<const rt_unary_expr<InterfaceType> *>(e.get());
        
          if (dynamic_cast<const IntegrationOperation *>(integrand->op()) != NULL)
          {
            const IntegrationOperation * op_tmp = dynamic_cast<const IntegrationOperation *>(integrand->op());
            return quadrature_rule_->eval(op_tmp->op().interval(), 
                                          rt_expr<InterfaceType>(integrand->clone()),
                                          op_tmp->op().variable());
          }
          else
            throw "Not implemented!";
        }
        else
          throw "Not implemented!";

        return ct_constant<1>();
      }

      rt_expr<InterfaceType> operator()(rt_interval<InterfaceType> const & interv,
                                        rt_expr<InterfaceType> const & e,
                                        rt_variable<InterfaceType> const & var) const
      {
        return quadrature_rule_->eval(interv, e, var);
      }

      template <unsigned long id>
      rt_expr<InterfaceType> operator()(rt_interval<InterfaceType> const & interv,
                                        rt_expr<InterfaceType> const & e,
                                        ct_variable<id> const & var) const
      {
        return quadrature_rule_->eval(interv, e, rt_variable<InterfaceType>(id));
      }

    private:
      std::auto_ptr<numerical_quadrature_interface<InterfaceType> > quadrature_rule_;
  };
  typedef rt_numerical_quadrature<>   numerical_quadrature;

}

#endif
