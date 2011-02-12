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
#include "viennamath/constant.hpp"
#include "viennamath/expression_compile_time.hpp"

namespace viennamath
{
  
  //A run time expression
  class unary_expr : public expression_interface
  {
    public:
//       explicit expr(expression_interface * lhs,
//                     op_interface         * op,
//                     expression_interface * rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
      unary_expr() {}

      explicit unary_expr(expression_interface * lhs,
                          op_interface         * op) : expr_(lhs),
                                                       op_(op) {}
                                                  
      explicit unary_expr(expression_interface * lhs) : expr_(lhs), 
                                                        op_(new op_unary<op_id>()) {}
                    
      /*template <typename LHS, typename OP, typename RHS>
      explicit expr(LHS const & lhs, OP const & op, RHS const & rhs) 
      {
        expr(&lhs, &op, &rhs); 
      }*/

      template <typename LHS, typename OP, typename RHS>
      explicit unary_expr(ct_expr<LHS, OP, RHS> const & other) : op_(new OP())
      {
        std::cout << "Constructing from expression " << other << std::endl;
        expr_ = std::auto_ptr<expression_interface>(other.lhs().clone());
      }

      template <unsigned long id>
      explicit unary_expr(variable<id> const & other) : expr_(other.clone()),
                                                 op_(new op_unary<op_id>())  {}

      template <typename T>
      explicit unary_expr(constant<T> const & other) : expr_(other.clone()),
                                              op_(op_unary<op_id>().clone()) {}

      template <long value>
      explicit unary_expr(ct_constant<value> const & other) : expr_(other.clone()),
                                                     op_(new op_unary<op_id>()) {}

      //Copy CTOR:
      unary_expr(unary_expr const & other) : expr_(other.expr_->clone()), 
                                             op_(other.op_->clone()) {};

      //assignments:                           
      template <typename LHS, typename OP, typename RHS>
      unary_expr & operator=(ct_expr<LHS, OP, RHS> const & other) 
      {
        expr_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        op_ = std::auto_ptr<op_interface>(new OP());
        return *this;
      }

      unary_expr & operator=(unary_expr const & other) 
      {
        expr_ = std::auto_ptr<expression_interface>(other.lhs()->clone());
        op_  = std::auto_ptr<op_interface>(other.op()->clone());
        return *this;
      }

      template <typename ScalarType>
      unary_expr & operator=(constant<ScalarType> const & other)
      {
        expr_ = std::auto_ptr<expression_interface>(other.clone());
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        return *this;
      }

      template <long value>
      unary_expr & operator=(ct_constant<value> const & other)
      {
        return *this = value;
      }

      unary_expr & operator=(numeric_type value)
      {
        expr_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        return *this;
      }

      const expression_interface   * lhs() const { return expr_.get(); }
      const op_interface           * op()  const { return op_.get(); }
      
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
      numeric_type operator()(viennamath::vector_1<T0> const & v) const
      {
        std::vector<double> stl_v(1);
        stl_v[0] = v[ct_index<0>()];
        return this->eval(stl_v);
      }

      template <typename T0, typename T1>
      numeric_type operator()(viennamath::vector_2<T0, T1> const & v) const
      {
        std::vector<double> stl_v(2);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        return this->eval(stl_v);
      }
      
      template <typename T0, typename T1, typename T2>
      numeric_type operator()(viennamath::vector_3<T0, T1, T2> const & v) const
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
        return op_->apply(expr_.get(), expr_.get(), v);
      }

      numeric_type eval(numeric_type val) const
      {
        return op_->apply(expr_.get(), expr_.get(), val);
      }

      ///////////////////// substitution /////////////////////////////
      
      
      expression_interface * optimize() const
      {
        if (expr_->is_constant())
          return new constant<numeric_type>(op_->apply(expr_->unwrap(), 
                                                       numeric_type() //argument is ignored, since constant expression
                                                      ) 
                                           );

        //TODO: Unwrap op_id()
        
        return clone();
      }
      
    
      ///////// other interface requirements ////////////////////////
      expression_interface * clone() const { return new unary_expr(expr_->clone(), op_->clone()); }
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
        return op_->apply(expr_->unwrap(), expr_->unwrap());
      }
      
      bool is_constant() const { return expr_->is_constant(); };
      
      expression_interface * substitute(const expr & e,
                                        const expr & repl) const
      {
        if (equal(e.get()))
          return repl.get()->clone();
        
        return new unary_expr(expr_->substitute(e, repl),
                              op_->clone());
      };
      
      bool equal(const expression_interface * other) const
      {
        if (dynamic_cast<const unary_expr *>(other) != NULL)
        {
           const unary_expr * temp = dynamic_cast<const unary_expr *>(other);
           
           return expr_->equal(temp->lhs())
                       && op_->equal(temp->op());
        }
        return expr_->equal(other); 
      }
      
      expression_interface * diff(const expr & diff_var) const
      {
        return op_->diff(expr_.get(), expr_.get(), diff_var);
      }
      
    private:
      std::auto_ptr<expression_interface>  expr_;
      std::auto_ptr<op_interface>          op_;
  };
  
  
  std::ostream& operator<<(std::ostream & stream, unary_expr const & e)
  {
    stream << "unary" 
           << e.str()
           << "";
    return stream;
  }
  
  
}

#endif