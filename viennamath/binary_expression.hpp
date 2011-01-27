/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_BINARY_EXPRESSION_CPP
#define VIENNAMATH_BINARY_EXPRESSION_CPP

#include <ostream>
#include <sstream>
#include <memory>
#include "viennamath/forwards.h"
#include "viennamath/constant.hpp"
#include "viennamath/expression_compile_time.hpp"
#include "viennamath/unary_expression.hpp"
#include "viennamath/expression.hpp"

namespace viennamath
{
  
  //A run time expression
  class binary_expr : public expression_interface
  {
    public:
//       explicit expr(expression_interface * lhs,
//                     op_interface         * op,
//                     expression_interface * rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
      binary_expr() {}

      explicit binary_expr(expression_interface * lhs,
                           op_interface         * op,
                           expression_interface * rhs) : lhs_(lhs),
                                                         op_(op),
                                                         rhs_(rhs) {}
                    
      template <typename LHS, typename OP, typename RHS>
      binary_expr(expression<LHS, OP, RHS> const & other) : op_(OP().clone())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs().clone());
      }

      template <typename LHS, typename OP, long value>
      binary_expr(expression<LHS, OP, ct_constant<value> > const & other) : op_(new OP())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
      }

      template <long value, typename OP, typename RHS>
      binary_expr(expression<ct_constant<value>, OP, RHS > const & other) : op_(new OP())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        rhs_ = std::auto_ptr<expression_interface>(other.rhs().clone());
      }

      template <long value1, typename OP, long value2>
      binary_expr(expression<ct_constant<value1>, OP, ct_constant<value2> > const & other) : op_(new op_unary<op_id>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(OP().apply(value1, value2)));
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(OP().apply(value1, value2)));
      }

      template <unsigned long id>
      binary_expr(variable<id> const & other) : lhs_(other.clone()),
                                                  op_(new op_unary<op_id>()),
                                                  rhs_(other.clone()) {}

      template <typename T>
      binary_expr(constant<T> const & other) : lhs_(other.clone()),
                                               op_(new op_unary<op_id>()),
                                               rhs_(other.clone()) {}

      template <long value>
      binary_expr(ct_constant<value> const & other) : lhs_(new constant<numeric_type>(value)),
                                                      op_(new op_unary<op_id>()),
                                                      rhs_(new constant<numeric_type>(value)) {}

      //Copy CTOR:
      binary_expr(binary_expr const & other) : lhs_(other.lhs_->clone()), 
                                               op_(other.op_->clone()),
                                               rhs_(other.rhs_->clone()) {}

      //assignments:                           
      template <typename LHS, typename OP, typename RHS>
      binary_expr & operator=(expression<LHS, OP, RHS> const & other) 
      {
        lhs_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        op_ = std::auto_ptr<op_interface>(OP().clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs().clone());
        return *this;
      }
      
      template <typename LHS, typename OP, long value>
      binary_expr & operator=(expression<LHS, OP, ct_constant<value> > const & other)
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        op_ = std::auto_ptr<op_interface>(OP().clone());
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        return *this;
      }

      template <long value, typename OP, typename RHS>
      binary_expr & operator=(expression<ct_constant<value>, OP, RHS > const & other)
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        op_ = std::auto_ptr<op_interface>(OP().clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs().clone());
        return *this;
      }

      template <long value1, typename OP, long value2>
      binary_expr & operator=(expression<ct_constant<value1>, OP, ct_constant<value2> > const & other)
      {
        std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(OP().apply(value1, value2)));
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(OP().apply(value1, value2)));
        return *this;
      }
      

      binary_expr & operator=(binary_expr const & other) 
      {
        lhs_ = std::auto_ptr<expression_interface>(other.lhs()->clone());
        op_  = std::auto_ptr<op_interface>(other.op()->clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs()->clone());
        return *this;
      }

      template <typename ScalarType>
      binary_expr & operator=(constant<ScalarType> const & other)
      {
        lhs_ = std::auto_ptr<expression_interface>(other.clone());
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        rhs_ = std::auto_ptr<expression_interface>(other.clone());
        return *this;
      }

      template <long value>
      binary_expr & operator=(ct_constant<value> const & other)
      {
        return *this = value;
      }

      binary_expr & operator=(numeric_type value)
      {
        lhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        op_  = std::auto_ptr<op_interface>(new op_unary<op_id>());
        rhs_ = std::auto_ptr<expression_interface>(new constant<numeric_type>(value));
        return *this;
      }

      const expression_interface   * lhs() const { return lhs_.get(); }
      const op_interface           * op()  const { return op_.get(); }
      const expression_interface   * rhs() const { return rhs_.get(); }
      
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
        return op_->apply(lhs_.get(), rhs_.get(), v);
      }

      numeric_type eval(numeric_type val) const
      {
        return op_->apply(lhs_.get(), rhs_.get(), val);
      }

      ///////////////////// substitution /////////////////////////////
      
      
      expression_interface * optimize()
      {
        if (lhs_->is_constant() && rhs_->is_constant())
        {
          return new constant<numeric_type>( unwrap() );
        }
        else if (lhs_->is_constant())
        {
          lhs_ = std::auto_ptr<expression_interface>( new constant<numeric_type>(lhs_->unwrap()) );
          rhs_ = std::auto_ptr<expression_interface>( rhs_->optimize() );
        }
        else if (rhs_->is_constant())
        {
          lhs_ = std::auto_ptr<expression_interface>(lhs_->optimize());
          rhs_ = std::auto_ptr<expression_interface>( new constant<numeric_type>(rhs_->unwrap()) );
        }
        
        else
        {
          lhs_ = std::auto_ptr<expression_interface>( lhs_->optimize() );
          rhs_ = std::auto_ptr<expression_interface>( rhs_->optimize() );
        }
        
        return this;        
      }
      
      template <unsigned long id, typename ReplacementType>
      expression_interface * substitute(variable<id> const & u,
                                        ReplacementType const & repl) const
      {
        expression_interface * ret = this->substitute(expr(u.clone()), expr(repl.clone()));
        if (dynamic_cast<const binary_expr *>(ret) != NULL)
        {
          //TODO: Remove mem leak!
          expression_interface * ret2 = ret->optimize();
          return new unary_expr(ret2, new op_unary< op_id >());
        }
        
        return new binary_expr(ret, new op_unary< op_id >(), ret);
      }
      
    
      ///////// other interface requirements ////////////////////////
      expression_interface * clone() const { return new binary_expr(lhs_->clone(), op_->clone(), rhs_->clone()); }
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
        //if (op_->is_unary())
        //  return lhs_->unwrap();
        return op_->apply(lhs_->unwrap(), rhs_->unwrap());
      }
      
      bool is_constant() const { return lhs_->is_constant() && rhs_->is_constant(); };
      
      expression_interface * substitute(const expr & e,
                                        const expr & repl) const
      {
        return new binary_expr(lhs_->substitute(e, repl),
                                    op_->clone(),
                                    rhs_->substitute(e, repl) ); 
      };
      
      bool equal(const expr & other) const
      {
        return lhs_->equal(other) && rhs_->equal(other);
      }
      
      template <unsigned long id>
      expression_interface * diff(variable<id> const & diff_var) const
      {
        return diff(expr(diff_var.clone())); 
      }
      
      expression_interface * diff(const expr & diff_var) const
      {
        return op_->diff(lhs_.get(), rhs_.get(), diff_var);
      }

      
    private:
      std::auto_ptr<expression_interface>  lhs_;
      std::auto_ptr<op_interface>          op_;
      std::auto_ptr<expression_interface>  rhs_;
  };
  
  
  std::ostream& operator<<(std::ostream & stream, binary_expr const & e)
  {
    stream << "expr" 
           << e.str()
           << "";
    return stream;
  }
  
  template <typename LHS, typename OP, typename RHS>
  expression_interface * expression<LHS, OP, RHS>::clone() const
  {
    return binary_expr(*this).clone();
  }
  
}

#endif