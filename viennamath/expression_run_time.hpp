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
#include "viennamath/expression_compile_time.hpp"

namespace viennamath
{
  //interface for dispatches:
  class expression_interface
  {
    public:
      virtual ~expression_interface() {}
      
      virtual expression_interface * clone() const = 0;
      virtual std::string print() const = 0;
      virtual bool is_primitive() const = 0;
  };
  
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
                    
      template <typename LHS, typename OP, typename RHS>
      explicit expr(LHS const & lhs, OP const & op, RHS const & rhs) 
      {
        expr(&lhs, &op, &rhs); 
      }

      template <typename LHS, typename OP, typename RHS>
      expr(expression<LHS, OP, RHS> const & other) : lhs_(other.lhs().clone()),
                                                     op_(OP().clone()),
                                                     rhs_(other.rhs().clone()) {}

      template <typename LHS, typename OP, typename RHS>
      expr & operator=(expression<LHS, OP, RHS> const & other) 
      {
        lhs_ = std::auto_ptr<expression_interface>(other.lhs().clone());
        op_ = std::auto_ptr<op_interface>(OP().clone());
        rhs_ = std::auto_ptr<expression_interface>(other.rhs().clone());
        return *this;
      }

      //Copy CTOR:
      expr(expr const & other) : lhs_(other.lhs_->clone()), 
                                 op_(other.op_->clone()),
                                 rhs_(other.rhs_->clone()) {};
      
      const expression_interface   * lhs() const { return lhs_.get(); }
      const op_interface           * op()  const { return op_.get(); }
      const expression_interface   * rhs() const { return rhs_.get(); }
    
      //interface requirements:
      expression_interface * clone() const { return new expr(lhs_->clone(), op_->clone(), rhs_->clone()); }
      std::string print() const
      {
        std::stringstream ss;
        ss << lhs_->print();
        ss << op_->print();
        ss << rhs_->print();
        return ss.str();        
      }
      bool is_primitive() const { return false; }
      
    private:
      std::auto_ptr<expression_interface>  lhs_;
      std::auto_ptr<op_interface>          op_;
      std::auto_ptr<expression_interface>  rhs_;
  };
  
  
  std::ostream& operator<<(std::ostream & stream, expr const & e)
  {
    stream << "expr(" 
           << e.lhs()->print() << e.op()->print() << e.rhs()->print() 
           << ")";
    return stream;
  }
  
}

#endif