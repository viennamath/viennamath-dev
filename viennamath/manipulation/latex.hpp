/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_LATEX_HPP
#define VIENNAMATH_LATEX_HPP

#include <map>

#include "viennamath/forwards.h"
#include "viennamath/runtime/unary_expression.hpp"
#include "viennamath/compiletime/unary_op_tags.hpp"

namespace viennamath
{
  
  // TODO: Handling parenthesis
  
  
  template <typename InterfaceType = default_interface_type>
  class rt_latex_translator
  {
      typedef typename InterfaceType::numeric_type                           NumericType;
    
      typedef viennamath::rt_binary_expr<InterfaceType>                      BinaryExpr;
      typedef viennamath::rt_unary_expr<InterfaceType>                       UnaryExpr;
      typedef viennamath::rt_constant<default_numeric_type, InterfaceType>   Constant;
      typedef viennamath::rt_variable<InterfaceType>                         Variable;
      typedef viennamath::rt_function_symbol<InterfaceType>                  FuncSymbol;
      typedef viennamath::rt_equation<InterfaceType>                         Equation;
      typedef viennamath::rt_interval<InterfaceType>                         Interval;
    
    public:

      //
      // Generic runtime expression. Unwrap it and then scan through types
      //
      std::string operator()(viennamath::rt_expr<InterfaceType> const & e,
                             bool use_parenthesis = false) const
      {
        std::string ret;
        
        ret = process_if_castable<BinaryExpr>(e.get(), use_parenthesis); if (ret.size() > 0) return ret;
        ret = process_if_castable<UnaryExpr >(e.get(), use_parenthesis); if (ret.size() > 0) return ret;
        ret = process_if_castable<Constant  >(e.get(), use_parenthesis); if (ret.size() > 0) return ret;
        ret = process_if_castable<Variable  >(e.get(), use_parenthesis); if (ret.size() > 0) return ret;
        ret = process_if_castable<FuncSymbol>(e.get(), use_parenthesis); if (ret.size() > 0) return ret;
        ret = process_if_castable<Equation  >(e.get(), use_parenthesis); if (ret.size() > 0) return ret;

        
        throw "Unknown type!";
        return "";
      }
      
      
      std::string operator()(BinaryExpr const & e) const { return process(e); }
      std::string operator()(UnaryExpr  const & e) const { return process(e); }

      template <typename ScalarType>
      std::string operator()(viennamath::rt_constant<ScalarType, InterfaceType> const & e) const { return process(e); }
      std::string operator()(Variable   const & e) const { return process(e); }
      std::string operator()(FuncSymbol const & e) const { return process(e); }
      std::string operator()(Equation   const & e) const { return process(e); }
      std::string operator()(Interval   const & e) const { return process(e); }
      
      
      void customize(Variable const & x, std::string output)
      {
        variable_strings_[x.id()] = output;
      }

      void customize(FuncSymbol const & x, std::string output)
      {
        function_symbol_strings_[std::pair<unsigned long, unsigned long>(x.id(), x.tag_id())] = output;
      }

    private:
      
      // Helper: Tries to cast to the provided type and returns the LaTeX string if successful. Otherwise, an empty string is returned.
      template <typename TargetType>
      std::string process_if_castable(InterfaceType const * ptr, bool use_parenthesis) const
      {
        if (dynamic_cast< const TargetType * >(ptr) != NULL)
        {
          const TargetType * temp = dynamic_cast< const TargetType * >(ptr);
          return process(*temp, use_parenthesis);
        }
        return "";
      }
      
      //
      // Binary expression
      //
      std::string process(viennamath::rt_binary_expr<InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;
        viennamath::rt_expr<InterfaceType> lhs(e.lhs()->clone());
        viennamath::rt_expr<InterfaceType> rhs(e.rhs()->clone());
        
        if (dynamic_cast< const op_binary<op_div<NumericType>, InterfaceType> * >(e.op()) != NULL)  //division -> \frac{}{}
        {
          if (use_parenthesis)
            ss << " \\left( ";
          ss << " \\frac{" << operator()(lhs) << "}{" << operator()(rhs) << "} ";
          if (use_parenthesis)
            ss << " \\right) ";
        }
        else
        {
          bool is_op_mult = false;
          if (dynamic_cast< const op_binary<op_mult<NumericType>, InterfaceType> * >(e.op()) != NULL)
            is_op_mult = true;
            
          if (use_parenthesis)
            ss << "(";
          ss << operator()(lhs, is_op_mult);
          if (is_op_mult)
            ss << "\\cdot";
          else
            ss << e.op()->str();
          ss << operator()(rhs, is_op_mult);
          if (use_parenthesis)
            ss << ")";
        }
        
        return ss.str();
      }
      
      //
      // Unary expression
      //
      std::string process(viennamath::rt_unary_expr<InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        typedef op_unary<op_id<NumericType>,    InterfaceType>    OpId;
        typedef op_unary<op_exp<NumericType>,   InterfaceType>    OpExp;
        typedef op_unary<op_sin<NumericType>,   InterfaceType>    OpSin;
        typedef op_unary<op_cos<NumericType>,   InterfaceType>    OpCos;
        typedef op_unary<op_tan<NumericType>,   InterfaceType>    OpTan;
        typedef op_unary<op_fabs<NumericType>,  InterfaceType>    OpFabs;
        typedef op_unary<op_sqrt<NumericType>,  InterfaceType>    OpSqrt;
        typedef op_unary<op_log<NumericType>,   InterfaceType>    OpLog;
        typedef op_unary<op_log10<NumericType>, InterfaceType>    OpLog10;
        
        // symbolic stuff:
        typedef op_unary<op_gradient<NumericType>, InterfaceType>              OpGradient;
        typedef op_unary<op_divergence<NumericType>, InterfaceType>            OpDivergence;
        typedef op_unary<op_partial_deriv<NumericType>, InterfaceType>         OpPartialDeriv;
        typedef op_unary<op_rt_integral<InterfaceType>, InterfaceType>         OpRuntimeIntegration;
        
        std::stringstream ss;
        viennamath::rt_expr<InterfaceType> lhs(e.lhs()->clone());
        
        if (dynamic_cast< const OpId * >(e.op()) != NULL)
          ss << operator()(lhs, use_parenthesis);
        else if (dynamic_cast< const OpExp * >(e.op()) != NULL)
          ss << " \\exp " << operator()(lhs, true) << " ";          
        else if (dynamic_cast< const OpSin * >(e.op()) != NULL)
          ss << " \\sin " << operator()(lhs, true) << " ";          
        else if (dynamic_cast< const OpCos * >(e.op()) != NULL)
          ss << " \\cos " << operator()(lhs, true) << " ";          
        else if (dynamic_cast< const OpTan * >(e.op()) != NULL)
          ss << " \\tan " << operator()(lhs, true) << " ";          
        else if (dynamic_cast< const OpFabs * >(e.op()) != NULL)
          ss << " \\left|" << operator()(lhs) << "\\right| ";          
        else if (dynamic_cast< const OpSqrt * >(e.op()) != NULL)
          ss << " \\sqrt{" << operator()(lhs) << "} ";          
        else if (dynamic_cast< const OpLog * >(e.op()) != NULL)
          ss << " \\ln " << operator()(lhs, true) << " ";          
        else if (dynamic_cast< const OpLog10 * >(e.op()) != NULL)
          ss << " \\log " << operator()(lhs, true) << " ";     
        
        else if (dynamic_cast< const OpGradient * >(e.op()) != NULL)
          ss << " \\nabla " << operator()(lhs, true) << " ";     
        else if (dynamic_cast< const OpDivergence * >(e.op()) != NULL)
          ss << " \\nabla \\cdot " << operator()(lhs, true) << " ";     
        else if (dynamic_cast< const OpPartialDeriv * >(e.op()) != NULL)
        {
          const OpPartialDeriv * tmp = dynamic_cast< const OpPartialDeriv * >(e.op());
          viennamath::rt_variable<InterfaceType> var(tmp->op().id());
          ss << " \\frac{\\partial " << operator()(lhs, true) << "}{\\partial " << process(var) << "} ";
        }
        else if (dynamic_cast< const OpRuntimeIntegration * >(e.op()) != NULL)
        {
          const OpRuntimeIntegration * op_integral = dynamic_cast< const OpRuntimeIntegration * >(e.op());
          // integral:
          if (op_integral->op().interval().is_symbolic())
            ss << " \\int_\\Omega ";
          else
            ss << " \\int_{ " << operator()(op_integral->op().interval()) << " } ";
                
          // integrand:
          ss << operator()(lhs) << " ";
          
          // integration variable:
          if (op_integral->op().interval().is_symbolic())
            ss << " \\: \\mathrm{d} \\Omega ";
          else
            ss << " \\: \\mathrm{d} " << operator()(op_integral->op().variable()) << " ";
        }
        else
          throw "Not supported!";
        
        return ss.str();
      }
      
      //
      // Constant
      //
      template <typename ScalarType>
      std::string process(viennamath::rt_constant<ScalarType, InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;

        ss << " " << static_cast<ScalarType>(e) << " ";
        
        return ss.str();        
      }

      //
      // Variable
      //
      std::string process(viennamath::rt_variable<InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;

        std::map<unsigned long, std::string>::const_iterator it = variable_strings_.find(e.id());
        if (it != variable_strings_.end())
          ss << it->second;
        else
          ss << " x_{" << e.id() << "} ";
        
        return ss.str();        
      }

      //
      // Function Symbol
      //
      std::string process(viennamath::rt_function_symbol<InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;
        
        std::pair<unsigned long, unsigned long> func_symb_id(e.id(), e.tag_id());
        std::map<std::pair<unsigned long, unsigned long>, std::string>::const_iterator it = function_symbol_strings_.find(func_symb_id);
        if (it != function_symbol_strings_.end())
        {
          ss << it->second;
        }
        else
        {
          if (e.tag_id() == test_tag<>::tag_id())
            ss << " v_{" << e.id() << "} ";
          else
            ss << " u_{" << e.id() << "} ";
        }
        
        return ss.str();        
      }

      //
      // Equation
      //
      std::string process(viennamath::rt_equation<InterfaceType> const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;

        ss << this->operator()(e.lhs()) << " = " << this->operator()(e.rhs());
        
        return ss.str();        
      }

      //
      // Interval
      //
      std::string process(Interval const & e,
                          bool use_parenthesis = false) const
      {
        std::stringstream ss;

        ss << " [ " << this->operator()(e.lower()) << "; " << this->operator()(e.upper()) << " ] ";
        
        return ss.str();        
      }


    std::map<unsigned long, std::string>                            variable_strings_;
    std::map<std::pair<unsigned long, unsigned long>, std::string>  function_symbol_strings_;
  };
  
  
  typedef rt_latex_translator<>      latex_translator;
  
}

#endif
