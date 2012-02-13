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
#include "viennamath/runtime/integral.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/eval.hpp"

namespace viennamath
{
  
  template <typename InterfaceType>
  class numerical_quadrature_interface
  {
    public:
      typedef typename InterfaceType::numeric_type   numeric_type;
      
      virtual numerical_quadrature_interface * clone() const = 0;
      
      virtual numeric_type eval(rt_interval<InterfaceType> const & interv,
                                rt_expr<InterfaceType> const & e,
                                rt_variable<InterfaceType> const & var) const = 0;
  };
  
  
  template <typename InterfaceType = default_interface_type>
  class rt_gauss_quad_1 : public numerical_quadrature_interface<InterfaceType>
  {
      typedef numerical_quadrature_interface<InterfaceType>  BaseType;
     
    public:
      typedef typename BaseType::numeric_type         numeric_type;
      
      enum { id = 1 };
      
      BaseType * clone() { return rt_gauss_quad_1(); }
      
      
      numeric_type eval(rt_interval<InterfaceType> const & interv,
                        rt_expr<InterfaceType> const & e,
                        rt_variable<InterfaceType> const & var) const
      {
        assert(interv.lower().get()->is_constant() && 
              interv.upper().get()->is_constant() && 
              "Upper or lower interval is not a constant!");
        
        numeric_type abscissa = (viennamath::eval(interv.lower(), 0.0) + viennamath::eval(interv.upper(), 0.0)) / 2.0;
        rt_expr<InterfaceType> tmp = viennamath::substitute(var, abscissa, e);
        return tmp.get()->unwrap() * viennamath::eval(interv.upper() - interv.lower(), 0.0);
      }
    private:
      std::vector<numeric_type> p_;
  };
  typedef rt_gauss_quad_1<>      gauss_quad_1;
  
  
  

  
  
  template <typename InterfaceType = default_interface_type>
  class rt_numerical_quadrature 
  {
    public:
      typedef typename InterfaceType::numeric_type        NumericT;
      
      //
      // Initialization, method 1: Provide an ID for predefined integration routines
      //
      /*rt_numerical_quadrature(unsigned long id)
      {
        if (id == 1)
          quadrature_rule_ = std::auto_ptr<numerical_quadrature_interface<InterfaceType> >(new rt_gauss_quad_1<InterfaceType>());
        else
          throw "Not supported!";
      }*/
      
      // Default CTOR for support with STL containers:
      rt_numerical_quadrature() {}
      
      
      //
      // Initialization, method 2: Provide pointer (ownership is taken!)
      //
      rt_numerical_quadrature(numerical_quadrature_interface<InterfaceType> * ptr) : quadrature_rule_(ptr) {}
      
      
      // Copy CTOR:
      rt_numerical_quadrature(const rt_numerical_quadrature & other) : quadrature_rule_(other.quadrature_rule_->clone()) {}


      // Copy CTOR:
      rt_numerical_quadrature & operator=(const rt_numerical_quadrature & other)
      {
        quadrature_rule_ = std::auto_ptr<numerical_quadrature_interface<InterfaceType> >(other.quadrature_rule_->clone());
        return *this;
      }

      
      NumericT operator()(rt_expr<InterfaceType> const & e) const
      {
        const rt_unary_expr<InterfaceType> * integral_expression = dynamic_cast<const rt_unary_expr<InterfaceType> *>(e.get());
        
        if (integral_expression != NULL)
        {
          typedef op_unary<op_rt_integral<InterfaceType>, InterfaceType>    IntegrationOperation;

          const IntegrationOperation * op_tmp = dynamic_cast<const IntegrationOperation *>(integral_expression->op());
          
          if (op_tmp != NULL)
          {
            return quadrature_rule_->eval(op_tmp->op().interval(), 
                                          rt_expr<InterfaceType>(integral_expression->lhs()->clone()),
                                          op_tmp->op().variable());
          }
          else
          {
            typedef op_unary<op_rt_symbolic_integral<InterfaceType>, InterfaceType>    SymbolicIntegrationOperation;

            const SymbolicIntegrationOperation * op_symb_tmp = dynamic_cast<const SymbolicIntegrationOperation *>(integral_expression->op());
            
            if (op_symb_tmp != NULL)
            {
              return quadrature_rule_->eval(op_tmp->op().interval(), 
                                            rt_expr<InterfaceType>(integral_expression->lhs()->clone()),
                                            op_tmp->op().variable());
            }
            
            std::cerr << "ERROR: No integral encountered in numerical quadrature!" << std::endl;
            std::cerr << e << std::endl;
            throw "Not implemented!";
          }
        }
        else
        {
          if (e.get()->is_constant())
          {
            if (e.get()->eval(0) == 0)
              return rt_constant<typename InterfaceType::numeric_type, InterfaceType>(0);
          }
          
          std::cerr << "ERROR: Non-unary expression encountered in numerical quadrature: NOT IMPLEMENTED!" << std::endl;
          std::cerr << e << std::endl;
          throw "Not implemented!";
        }

        return 0;
      }

      NumericT operator()(rt_interval<InterfaceType> const & interv,
                                        rt_expr<InterfaceType> const & e,
                                        rt_variable<InterfaceType> const & var) const
      {
        return quadrature_rule_->eval(interv, e, var);
      }

      template <unsigned long id>
      NumericT operator()(rt_interval<InterfaceType> const & interv,
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

