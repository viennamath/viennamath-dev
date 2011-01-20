/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_RUN_TIME_CPP
#define VIENNAMATH_EXPRESSION_RUN_TIME_CPP

#include <ostream>
#include <sstream>
#include <memory>
#include "viennamath/forwards.h"
#include "viennamath/constant.hpp"
#include "viennamath/expression_compile_time.hpp"

namespace viennamath
{
  
  //A run time expression
  class expr : public expression_interface
  {
    public:
//       explicit expr(expression_interface * lhs,
//                     op_interface         * op,
//                     expression_interface * rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
      expr() {}

      explicit expr(expression_interface * lhs,
                    op_interface         * op,
                    expression_interface * rhs) : lhs_(lhs->clone()), op_(op->clone()), rhs_(rhs->clone()) {}
                    
      /*template <typename LHS, typename OP, typename RHS>
      explicit expr(LHS const & lhs, OP const & op, RHS const & rhs) 
      {
        expr(&lhs, &op, &rhs); 
      }*/

      template <typename LHS, typename OP, typename RHS>
      expr(expression<LHS, OP, RHS> const & other) : op_(OP().clone())
      {
        expr temp1(other.lhs());
        expr temp2(other.rhs());
        
        lhs_ = std::auto_ptr<expression_interface>(temp1.clone());
        rhs_ = std::auto_ptr<expression_interface>(temp2.clone());
      }

      template <typename T, unsigned long id>
      expr(unknown<T, id> const & other) : lhs_(other.clone()),
                                           op_(op_unary<op_id>().clone()),
                                           rhs_(other.clone()) {}

      template <typename T>
      expr(constant<T> const & other) : lhs_(other.clone()),
                                           op_(op_unary<op_id>().clone()),
                                           rhs_(other.clone()) {}

      template <long value>
      expr(ct_constant<value> const & other) : lhs_(other.clone()),
                                                         op_(op_unary<op_id>().clone()),
                                                         rhs_(other.clone()) {}

      //Copy CTOR:
      expr(expr const & other) : lhs_(other.lhs_->clone()), 
                                 op_(other.op_->clone()),
                                 rhs_(other.rhs_->clone()) {};

      //assignments:                           
      template <typename LHS, typename OP, typename RHS>
      expr & operator=(expression<LHS, OP, RHS> const & other) 
      {
        expr temp1(other.lhs());
        expr temp2(other.rhs());
        
        lhs_ = std::auto_ptr<expression_interface>(temp1.clone());
        op_ = std::auto_ptr<op_interface>(OP().clone());
        rhs_ = std::auto_ptr<expression_interface>(temp2.clone());
        return *this;
      }

      expr & operator=(expr const & other) 
      {
        lhs_ = std::auto_ptr<expression_interface>(other.lhs()->clone());
        op_  = std::auto_ptr<op_interface>(other.op()->clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs()->clone());
        return *this;
      }

      template <typename ScalarType>
      expr & operator=(constant<ScalarType> const & other)
      {
        lhs_ = std::auto_ptr<expression_interface>(other.clone());
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        rhs_ = std::auto_ptr<expression_interface>(other.clone());
        return *this;
      }

      template <long value>
      expr & operator=(ct_constant<value> const & other)
      {
        return *this = value;
      }

      expr & operator=(numeric_type value)
      {
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        return *this;
      }

      const expression_interface   * lhs() const { return lhs_.get(); }
      const op_interface           * op()  const { return op_.get(); }
      const expression_interface   * rhs() const { return rhs_.get(); }
      
      //evaluation:
      expr operator()(numeric_type val) const
      {
        std::vector<numeric_type> v(1);
        v[0] = val;
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }

      template <typename ScalarType>
      expr operator()(constant<ScalarType> val) const
      {
        std::vector<numeric_type> v(1);
        v[0] = static_cast<numeric_type>(val);
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }
      
      template <long value>
      expr operator()(ct_constant<value> val) const
      {
        std::vector<numeric_type> v(1);
        v[0] = value;
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }
      

      template <typename VectorType>
      expr operator()(VectorType const & v) const
      {
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }

      template <typename T0>
      expr operator()(viennamath::vector_1<T0> const & v) const
      {
        std::vector<double> stl_v(1);
        stl_v[0] = v[ct_index<0>()];
        return op_->apply(lhs_.get(), rhs_.get(), stl_v);
      }

      template <typename T0, typename T1>
      expr operator()(viennamath::vector_2<T0, T1> const & v) const
      {
        std::vector<double> stl_v(2);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        return op_->apply(lhs_.get(), rhs_.get(), stl_v);
      }
      
      template <typename T0, typename T1, typename T2>
      expr operator()(viennamath::vector_3<T0, T1, T2> const & v) const
      {
        std::vector<double> stl_v(3);
        stl_v[0] = v[ct_index<0>()];
        stl_v[1] = v[ct_index<1>()];
        stl_v[2] = v[ct_index<2>()];
        return op_->apply(lhs_.get(), rhs_.get(), stl_v);
      }
      
      expr eval(std::vector<double> const & v) const
      {
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }
    
      //interface requirements:
      expression_interface * clone() const { return new expr(lhs_->clone(), op_->clone(), rhs_->clone()); }
      std::string str() const
      {
        std::stringstream ss;
        ss << "(";
        if (op_->is_unary())
        {
          ss << op_->str();
          ss << "(";
          ss << lhs_->str();
          ss << ")";
        }
        else
        {
          ss << lhs_->str();
          ss << op_->str();
          ss << rhs_->str();
        }
        ss << ")";
        return ss.str();        
      }
      bool is_unary() const { return false; }
      
      numeric_type unwrap() const
      {
        if (op_->is_unary())
          return lhs_->unwrap();
        return op_->apply(lhs_->unwrap(), rhs_->unwrap());
      }
      
    private:
      std::auto_ptr<expression_interface>  lhs_;
      std::auto_ptr<op_interface>          op_;
      std::auto_ptr<expression_interface>  rhs_;
  };
  
  
  std::ostream& operator<<(std::ostream & stream, expr const & e)
  {
    stream << "expr" 
           << e.str()
           << "";
    return stream;
  }
  
  template <typename ScalarType>
  expr constant<ScalarType>::eval(std::vector<double> const & v) const { return (*this)(v); }
  
  
}

#endif