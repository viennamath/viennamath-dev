/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNARY_EXPRESSION_CPP
#define VIENNAMATH_UNARY_EXPRESSION_CPP

#include <iostream>
#include <ostream>
#include <sstream>
#include <memory>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/unary_op_tags.hpp"
#include "viennamath/compiletime/ct_expr.hpp"
#include "viennamath/runtime/constant.hpp"
#include "viennamath/runtime/op_interface.hpp"
#include "viennamath/runtime/expression_interface.hpp"

namespace viennamath
{
  
  //A run time expression
  template <typename InterfaceType /* see forwards.h for default argument */>
  class unary_expr : public InterfaceType
  {
    typedef op_interface<InterfaceType>                    op_interface_type;
    typedef op_unary<op_id<typename InterfaceType::numeric_type>, InterfaceType>  op_unary_id_type;
    
    public:
      typedef typename InterfaceType::numeric_type         numeric_type;
      
//       explicit expr(InterfaceType * lhs,
//                     op_interface         * op,
//                     InterfaceType * rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
      unary_expr() {}

      explicit unary_expr(InterfaceType * lhs,
                          op_interface_type * op) : expr_(lhs),
                                                    op_(op) {}
                                                  
      explicit unary_expr(InterfaceType * lhs) : expr_(lhs), 
                                                 op_(new op_unary_id_type()) {}
                    
      /*template <typename LHS, typename OP, typename RHS>
      explicit expr(LHS const & lhs, OP const & op, RHS const & rhs) 
      {
        expr(&lhs, &op, &rhs); 
      }*/

      template <typename LHS, typename OP, typename RHS>
      explicit unary_expr(ct_expr<LHS, OP, RHS> const & other) : op_(new OP())
      {
        std::cout << "Constructing from expression " << other << std::endl;
        expr_ = std::auto_ptr<InterfaceType>(other.lhs().clone());
      }

      explicit unary_expr(variable<InterfaceType> const & other) : expr_(other.clone()),
                                                                   op_(new op_unary_id_type())  {}

      template <typename T>
      explicit unary_expr(constant<T, InterfaceType> const & other) : expr_(other.clone()),
                                                                      op_(new op_unary_id_type()) {}

      template <long value>
      explicit unary_expr(ct_constant<value> const & other) : expr_(other.clone()),
                                                              op_(new op_unary_id_type()) {}

      //Copy CTOR:
      unary_expr(unary_expr const & other) : expr_(other.expr_->clone()), 
                                             op_(other.op_->clone()) {};

      //assignments:                           
      template <typename LHS, typename OP, typename RHS>
      unary_expr & operator=(ct_expr<LHS, OP, RHS> const & other) 
      {
        expr_ = std::auto_ptr<InterfaceType>(other.lhs().clone());
        op_ = std::auto_ptr<op_interface_type>(new OP());
        return *this;
      }

      unary_expr & operator=(unary_expr const & other) 
      {
        expr_ = std::auto_ptr<InterfaceType>(other.lhs_->clone());
        op_  = std::auto_ptr<op_interface_type>(other.op_->clone());
        return *this;
      }

      template <typename ScalarType>
      unary_expr & operator=(constant<ScalarType> const & other)
      {
        expr_ = std::auto_ptr<InterfaceType>(other.clone());
        op_  = std::auto_ptr<op_interface_type>(new op_unary_id_type());
        return *this;
      }

      template <long value>
      unary_expr & operator=(ct_constant<value> const & other)
      {
        return *this = value;
      }

      unary_expr & operator=(numeric_type value)
      {
        expr_ = std::auto_ptr<InterfaceType>(new constant<numeric_type>(value));
        op_  = std::auto_ptr<op_interface_type>(new op_unary_id_type());
        return *this;
      }

      //const InterfaceType     * lhs() const { return expr_.get(); }
      //const op_interface_type * op()  const { return op_.get(); }
      
      ///////////////// evaluation: ///////////////////////////////
      
      //operator() is a convenience layer:
      numeric_type operator()(numeric_type val) const
      {
        return this->eval(val);
      }

      template <typename ScalarType>
      numeric_type operator()(constant<ScalarType> val) const
      {
        return this->eval(static_cast<numeric_type>(val));
      }
      
      template <long value>
      numeric_type operator()(ct_constant<value> val) const
      {
        return this->eval(value);
      }

      template <typename VectorType>
      numeric_type operator()(VectorType const & v) const
      {
        std::vector<double> stl_v(v.size());
        for (size_t i=0; i<v.size(); ++i)
          stl_v[i] = v[i];
        
        return this->eval(stl_v);
      }

      numeric_type operator()(std::vector<numeric_type> const & stl_v) const
      {
        return this->eval(stl_v);
      }

      template <typename T0>
      numeric_type operator()(viennamath::ct_vector_1<T0> const & v) const
      {
        std::vector<double> stl_v(1);
        stl_v[0] = v[ct_index<0>()];
        return this->eval(stl_v);
      }

      template <typename T0, typename T1>
      numeric_type operator()(viennamath::ct_vector_2<T0, T1> const & v) const
      {
        std::vector<double> stl_v(2);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        return this->eval(stl_v);
      }
      
      template <typename T0, typename T1, typename T2>
      numeric_type operator()(viennamath::ct_vector_3<T0, T1, T2> const & v) const
      {
        std::vector<double> stl_v(3);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        stl_v[2] = v[ct_index<2>()];
        return this->eval(stl_v);
      }
      
      //virtual functions for evaluations
      numeric_type eval(std::vector<double> const & v) const
      {
        return op_->apply(expr_.get()->eval(v));
      }

      numeric_type eval(numeric_type val) const
      {
        return op_->apply(expr_.get()->eval(val));
      }

      ///////////////////// substitution /////////////////////////////
      
      
      InterfaceType * optimize() const
      {
        if (expr_->is_constant())
          return new constant<numeric_type>( op_->apply(expr_->unwrap()) );

        //TODO: Unwrap op_id()
        
        return new unary_expr(expr_->optimize(), op_->clone());
      }
      
    
      ///////// other interface requirements ////////////////////////
      InterfaceType * clone() const { return new unary_expr(expr_->clone(), op_->clone()); }
      std::string str() const
      {
        std::stringstream ss;
        ss << op_->str();
        ss << "(";
        ss << expr_->str();
        ss << ")";
        return ss.str();        
      }
      
      numeric_type unwrap() const
      {
        //if (op_->is_unary())
        //  return lhs_->unwrap();
        return op_->apply(expr_->unwrap());
      }
      
      //bool is_constant() const { return expr_->is_constant(); };
      
      InterfaceType * substitute(const InterfaceType * e,
                                 const InterfaceType * repl) const
      {
        if (equal(e))
          return repl->clone();
        
        return new unary_expr(expr_->substitute(e, repl),
                              op_->clone());
      };
      
      bool equal(const InterfaceType * other) const
      {
        if (dynamic_cast<const unary_expr *>(other) != NULL)
        {
           const unary_expr * temp = dynamic_cast<const unary_expr *>(other);
           
           return expr_->equal(temp->expr_.get())
                  && op_->equal(temp->op_.get());
        }
        return expr_->equal(other); 
      }
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        return op_->diff(expr_.get(), diff_var);
      }
      
      const InterfaceType * lhs() const { return expr_.get(); }
      
    private:
      std::auto_ptr<InterfaceType>      expr_;
      std::auto_ptr<op_interface_type>  op_;
  };
  
  
  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, unary_expr<InterfaceType> const & e)
  {
    stream << "unary" 
           << e.str()
           << "";
    return stream;
  }
  
  
}

#endif