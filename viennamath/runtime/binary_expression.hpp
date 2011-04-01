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
#include "viennamath/runtime/constant.hpp"
#include "viennamath/runtime/binary_operators.hpp"
#include "viennamath/compiletime/ct_expr.hpp"
#include "viennamath/runtime/unary_expression.hpp"
#include "viennamath/runtime/op_interface.hpp"
#include "viennamath/runtime/expression_interface.hpp"
#include "viennamath/runtime/unary_operators.hpp"

namespace viennamath
{
  
  //A run time expression
  template <typename InterfaceType /* see forwards.h for default argument */>
  class binary_expr : public InterfaceType
  {
    typedef op_interface<InterfaceType>                                           op_interface_type;
    typedef op_unary<op_id<typename InterfaceType::numeric_type>, InterfaceType>  op_unary_id_type;
    
    public:
      typedef typename InterfaceType::numeric_type         numeric_type;
//       explicit expr(InterfaceType * lhs,
//                     op_interface         * op,
//                     InterfaceType * rhs) : lhs_(lhs), op_(op), rhs_(rhs) {}
      binary_expr() {}

      explicit binary_expr(InterfaceType * lhs,
                           op_interface_type         * op,
                           InterfaceType * rhs) : lhs_(lhs),
                                                         op_(op),
                                                         rhs_(rhs) {}
                    
      template <typename LHS, typename OP, typename RHS>
      explicit binary_expr(ct_expr<LHS, OP, RHS> const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.lhs()));
        rhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.rhs()));
      }

      /////////////// special case: ct_constant involved: ////////////////////////
      template <typename LHS, typename OP, long value>
      explicit binary_expr(ct_expr<LHS, OP, ct_constant<value> > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.lhs()));
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
      }

      template <long value, typename OP, typename RHS>
      explicit binary_expr(ct_expr<ct_constant<value>, OP, RHS > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        rhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.rhs()));
      }

      template <long value1, typename OP, long value2>
      explicit binary_expr(ct_expr<ct_constant<value1>, OP, ct_constant<value2> > const & other) : op_(new op_unary_id_type())
      {
        //std::cout << "Constructing from expression " << other << " to " << OP::apply(value1, value2) << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(OP::apply(value1, value2)));
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(OP::apply(value1, value2)));
      }

      /////////////////// special case: ct_variable involved: //////////////////////////
      template <typename LHS, typename OP, id_type id>
      explicit binary_expr(ct_expr<LHS, OP, ct_variable<id> > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.lhs()));
        rhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id));
      }

      template <id_type id, typename OP, typename RHS>
      explicit binary_expr(ct_expr<ct_variable<id>, OP, RHS > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id));
        rhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.rhs()));
      }

      template <id_type id1, typename OP, id_type id2>
      explicit binary_expr(ct_expr<ct_variable<id1>, OP, ct_variable<id2> > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << " to " << OP::apply(value1, value2) << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id1));
        rhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id2));
      }

      //resolving ambiguities:
      template <id_type id, typename OP, long value>
      explicit binary_expr(ct_expr<ct_variable<id>, OP, ct_constant<value> > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << " to " << OP::apply(value1, value2) << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id));
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
      }

      template <id_type id, typename OP, long value>
      explicit binary_expr(ct_expr<ct_constant<value>, OP, ct_variable<id> > const & other) : op_(new op_binary<OP, InterfaceType>())
      {
        //std::cout << "Constructing from expression " << other << " to " << OP::apply(value1, value2) << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        rhs_ = std::auto_ptr<InterfaceType>(new variable<InterfaceType>(id));
      }

      /*explicit binary_expr(variable<InterfaceType> const & other) : lhs_(other.clone()),
                                                                    op_(new op_unary_id_type()),
                                                                    rhs_(other.clone()) {}


      template <typename T>
      explicit binary_expr(constant<T> const & other) : lhs_(other.clone()),
                                                        op_(new op_unary_id_type()),
                                                        rhs_(other.clone()) {}

      template <long value>
      explicit binary_expr(ct_constant<value> const & other) : lhs_(new constant<numeric_type, InterfaceType>(value)),
                                                               op_(new op_unary_id_type()),
                                                               rhs_(new constant<numeric_type, InterfaceType>(value)) {}  */

      //Copy CTOR:
      binary_expr(binary_expr const & other) : lhs_(other.lhs_->clone()), 
                                               op_(other.op_->clone()),
                                               rhs_(other.rhs_->clone()) {}

      //assignments:                           
      template <typename LHS, typename OP, typename RHS>
      binary_expr & operator=(ct_expr<LHS, OP, RHS> const & other) 
      {
        lhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.lhs()));
        op_ = std::auto_ptr<op_interface_type>(new op_binary<OP, InterfaceType>());
        rhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.rhs()));
        return *this;
      }
      
      template <typename LHS, typename OP, long value>
      binary_expr & operator=(ct_expr<LHS, OP, ct_constant<value> > const & other)
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.lhs()));
        op_ = std::auto_ptr<op_interface_type>(new op_binary<OP, InterfaceType>());
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        return *this;
      }

      template <long value, typename OP, typename RHS>
      binary_expr & operator=(ct_expr<ct_constant<value>, OP, RHS > const & other)
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        op_ = std::auto_ptr<op_interface_type>(new op_binary<OP, InterfaceType>());
        rhs_ = std::auto_ptr<InterfaceType>(new binary_expr<InterfaceType>(other.rhs()));
        return *this;
      }

      template <long value1, typename OP, long value2>
      binary_expr & operator=(ct_expr<ct_constant<value1>, OP, ct_constant<value2> > const & other)
      {
        //std::cout << "Constructing from expression " << other << std::endl;
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(OP().apply(value1, value2)));
        op_  = std::auto_ptr<op_interface_type>(new op_unary_id_type());
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(OP().apply(value1, value2)));
        return *this;
      }
      

      binary_expr & operator=(binary_expr const & other) 
      {
        lhs_ = std::auto_ptr<InterfaceType>(other.lhs()->clone());
        op_  = std::auto_ptr<op_interface_type>(other.op()->clone());
        rhs_ = std::auto_ptr<InterfaceType>(other.rhs()->clone());
        return *this;
      }

      template <typename ScalarType>
      binary_expr & operator=(constant<ScalarType> const & other)
      {
        lhs_ = std::auto_ptr<InterfaceType>(other.clone());
        op_  = std::auto_ptr<op_interface_type>(new op_unary_id_type());
        rhs_ = std::auto_ptr<InterfaceType>(other.clone());
        return *this;
      }

      template <long value>
      binary_expr & operator=(ct_constant<value> const & other)
      {
        return *this = value;
      }

      binary_expr & operator=(numeric_type value)
      {
        lhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        op_  = std::auto_ptr<op_interface_type>(new op_unary_id_type());
        rhs_ = std::auto_ptr<InterfaceType>(new constant<numeric_type, InterfaceType>(value));
        return *this;
      }

      const InterfaceType      * lhs() const { return lhs_.get(); }
      const op_interface_type  * op()  const { return op_.get(); }
      const InterfaceType      * rhs() const { return rhs_.get(); }
      
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
        return op_->apply(lhs_.get()->eval(v), rhs_.get()->eval(v));
      }

      numeric_type eval(numeric_type val) const
      {
        return op_->apply(lhs_.get()->eval(val), rhs_.get()->eval(val));
      }

      ///////////////////// substitution /////////////////////////////
      
      
      InterfaceType * optimize() const
      {
        if (lhs_->is_constant() && rhs_->is_constant())
          return new constant<numeric_type>( unwrap() );
        
        //std::cout << "Optimization forwarded to " << op_->str() << std::endl;
        return op_->optimize(lhs_.get(), rhs_.get());
      }
      
      bool optimizable() const
      {
        if (lhs_->is_constant() && rhs_->is_constant())
        {
          //std::cout << "optimizable(): true in binary_expr" << std::endl;
          return true;
        }
        return op_->optimizable(lhs_.get(), rhs_.get());
      }
      
      ///////// other interface requirements ////////////////////////
      InterfaceType * clone() const { return new binary_expr(lhs_->clone(), op_->clone(), rhs_->clone()); }
      std::string str() const
      {
        std::stringstream ss;
        ss << "(";
        ss << lhs_->str();
        ss << op_->str();
        ss << rhs_->str();
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
      
      InterfaceType * substitute(const InterfaceType * e,
                                 const InterfaceType * repl) const
      {
        if (equal(e))
          return repl->clone();
        
        return new binary_expr(lhs_->substitute(e, repl),
                               op_->clone(),
                               rhs_->substitute(e, repl) ); 
      };
      
      bool equal(const InterfaceType * other) const
      {
        if (dynamic_cast< const binary_expr * >(other) != NULL)
        {
          const binary_expr * temp = dynamic_cast< const binary_expr * >(other);
          return lhs_->equal(temp->lhs())
                 && op_->equal(temp->op())
                 && rhs_->equal(temp->rhs());
        }
        return lhs_->equal(other) && rhs_->equal(other);
      }
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        return op_->diff(lhs_.get(), rhs_.get(), diff_var);
      }

      
    private:
      std::auto_ptr<InterfaceType>         lhs_;
      std::auto_ptr<op_interface_type>     op_;
      std::auto_ptr<InterfaceType>         rhs_;
  };
  
  
  template <typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, binary_expr<InterfaceType> const & e)
  {
    stream << "expr" 
           << e.str()
           << "";
    return stream;
  }

  template <typename T, typename InterfaceType>
  InterfaceType * op_unary<T, InterfaceType>::optimize(const InterfaceType * lhs,
                                                      const InterfaceType * rhs) const
  {
    return new binary_expr<InterfaceType>(lhs->clone(),
                                          new op_unary<T, InterfaceType>(),
                                          rhs->clone());
  }
  
}

#endif