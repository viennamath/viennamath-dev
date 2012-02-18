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
  template <typename InterfaceType = default_interface_type>
  class rt_latex_processor_interface
  {
    public: 
      virtual std::string process(InterfaceType const * e, bool use_parenthesis, rt_latex_translator<InterfaceType> const &) const = 0;
      virtual bool customize(InterfaceType const * e, std::string const & str) { return false; }
  };
  
  
  template <typename InterfaceType>
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
      
      typedef rt_latex_processor_interface<InterfaceType>                    ProcessorInterface;
      typedef std::vector< ProcessorInterface *>                             ProcessorArray;
    
    public:
      
      rt_latex_translator()
      {
        processors_.push_back(new rt_latex_binary_expr_processor<InterfaceType>());
        processors_.push_back(new rt_latex_unary_expr_processor<InterfaceType>());
        processors_.push_back(new rt_latex_constant_processor<InterfaceType>());
        processors_.push_back(new rt_latex_variable_processor<InterfaceType>());
        processors_.push_back(new rt_latex_function_symbol_processor<InterfaceType>());
      }
      
      ~rt_latex_translator()
      {
        for (typename ProcessorArray::iterator it = processors_.begin();
                                               it != processors_.end();
                                             ++it)
        {
          delete *it;
        }
      }

      //
      // Generic runtime expression. Unwrap it and then scan through types
      //
      std::string operator()(viennamath::rt_expr<InterfaceType> const & e,
                             bool use_parenthesis = false) const
      {
        return process_impl(e.get(), use_parenthesis);
      }
      
      std::string operator()(BinaryExpr const & e, bool use_parenthesis = false) const { return process_impl(&e, use_parenthesis); }
      std::string operator()(UnaryExpr  const & e, bool use_parenthesis = false) const { return process_impl(&e, use_parenthesis); }

      template <typename ScalarType>
      std::string operator()(viennamath::rt_constant<ScalarType, InterfaceType> const & e, bool use_parenthesis = false) const { return process_impl(e, use_parenthesis); }
      std::string operator()(Variable   const & e, bool use_parenthesis = false) const { return process_impl(&e, use_parenthesis); }
      std::string operator()(FuncSymbol const & e, bool use_parenthesis = false) const { return process_impl(&e, use_parenthesis); }
      std::string operator()(Equation   const & e, bool use_parenthesis = false) const
      {
        std::stringstream ss;
        ss << operator()(e.lhs()) << " = " << operator()(e.rhs());
        return ss.str();        
      }
      std::string operator()(Interval   const & e, bool use_parenthesis = false) const 
      {
        std::stringstream ss;
        ss << " [ " << operator()(e.lower()) << "; " << operator()(e.upper()) << " ] ";
        return ss.str();        
      }
      
      template <typename ExpressionType>
      void customize(ExpressionType const & e, std::string output)
      {
        bool found = false;
        for (typename ProcessorArray::const_iterator it = processors_.begin();
                                                     it != processors_.end();
                                                   ++it)
        {
          found |= (*it)->customize(&e, output);
        }       
        
        if (!found)
          std::cerr << "Warning: Cannot customize LaTeX translator for " << e << " (no suitable processor found)" << std::endl;
        //variable_strings_[x.id()] = output;
      }
      
      void add_processor(ProcessorInterface * proc_ptr)
      {
        processors_.push_back(proc_ptr);
      }

    private:
      
      std::string process_impl(InterfaceType const * ptr,
                               bool use_parenthesis = false) const
      {
        std::string ret;
        
        for (typename ProcessorArray::const_iterator it = processors_.begin();
                                                     it != processors_.end();
                                                   ++it)
        {
          ret = (*it)->process(ptr, use_parenthesis, *this);
          if (ret.size() > 0)
            return ret;
        }       
        
        std::cerr << "Unknown type in latex translator: " << ptr << std::endl;
        throw "Unknown type!";
        return "";
      }
      
    ProcessorArray processors_;
  };
  
  typedef rt_latex_translator<>      latex_translator;

  
  
  //
  // Binary expression
  //
  template <typename InterfaceType>
  class rt_latex_binary_expr_processor : public rt_latex_processor_interface<InterfaceType>
  {
      typedef typename InterfaceType::numeric_type           NumericType;
      typedef viennamath::rt_binary_expr<InterfaceType>      BinaryExpr;
    
    public:
      
      std::string process(InterfaceType const * ptr, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        if (dynamic_cast< const BinaryExpr * >(ptr) != NULL)
        {
          const BinaryExpr * temp = dynamic_cast< const BinaryExpr * >(ptr);
          return process_impl(*temp, use_parenthesis, translator);
        }
        
        return "";
      }
       
    private:

      std::string process_impl(BinaryExpr const & e, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        std::stringstream ss;
        viennamath::rt_expr<InterfaceType> lhs(e.lhs()->clone());
        viennamath::rt_expr<InterfaceType> rhs(e.rhs()->clone());
        
        if (dynamic_cast< const op_binary<op_div<NumericType>, InterfaceType> * >(e.op()) != NULL)  //division -> \frac{}{}
        {
          if (use_parenthesis)
            ss << " \\left( ";
          ss << " \\frac{" << translator(lhs) << "}{" << translator(rhs) << "} ";
          if (use_parenthesis)
            ss << " \\right) ";
        }
        else
        {
          bool is_op_mult = false;
          if (dynamic_cast< const op_binary<op_mult<NumericType>, InterfaceType> * >(e.op()) != NULL)
            is_op_mult = true;

          bool is_op_minus = false;
          if (dynamic_cast< const op_binary<op_minus<NumericType>, InterfaceType> * >(e.op()) != NULL)
            is_op_minus = true;
          
          if (use_parenthesis)
            ss << "(";
          ss << translator(lhs, is_op_mult);
          if (is_op_mult)
            ss << " \\cdot ";
          else
            ss << " " << e.op()->str() << " ";
          ss << translator(rhs, is_op_mult || is_op_minus);
          if (use_parenthesis)
            ss << ")";
        }
        
        return ss.str();
      }      
      
  }; 
  

  
  //
  // Unary expression
  //
  template <typename InterfaceType>
  class rt_latex_unary_expr_processor : public rt_latex_processor_interface<InterfaceType>
  {
      typedef typename InterfaceType::numeric_type           NumericType;
      typedef viennamath::rt_unary_expr<InterfaceType>       UnaryExpr;
    
    public:
      
      std::string process(InterfaceType const * ptr, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        if (dynamic_cast< const UnaryExpr * >(ptr) != NULL)
        {
          const UnaryExpr * temp = dynamic_cast< const UnaryExpr * >(ptr);
          return process_impl(*temp, use_parenthesis, translator);
        }
        
        return "";
      }
       
    private:

      std::string process_impl(UnaryExpr const & e, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
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
        typedef op_unary<op_rt_symbolic_integral<InterfaceType>, InterfaceType>         OpSymbolicIntegration;
        
        std::stringstream ss;
        viennamath::rt_expr<InterfaceType> lhs(e.lhs()->clone());
        
        if (dynamic_cast< const OpId * >(e.op()) != NULL)
          ss << translator(lhs, use_parenthesis);
        else if (dynamic_cast< const OpExp * >(e.op()) != NULL)
          ss << " \\exp " << translator(lhs, true) << " ";          
        else if (dynamic_cast< const OpSin * >(e.op()) != NULL)
          ss << " \\sin " << translator(lhs, true) << " ";          
        else if (dynamic_cast< const OpCos * >(e.op()) != NULL)
          ss << " \\cos " << translator(lhs, true) << " ";          
        else if (dynamic_cast< const OpTan * >(e.op()) != NULL)
          ss << " \\tan " << translator(lhs, true) << " ";          
        else if (dynamic_cast< const OpFabs * >(e.op()) != NULL)
          ss << " \\left|" << translator(lhs) << "\\right| ";          
        else if (dynamic_cast< const OpSqrt * >(e.op()) != NULL)
          ss << " \\sqrt{" << translator(lhs) << "} ";          
        else if (dynamic_cast< const OpLog * >(e.op()) != NULL)
          ss << " \\ln " << translator(lhs, true) << " ";          
        else if (dynamic_cast< const OpLog10 * >(e.op()) != NULL)
          ss << " \\log " << translator(lhs, true) << " ";     
        
        else if (dynamic_cast< const OpGradient * >(e.op()) != NULL)
          ss << " \\nabla " << translator(lhs, true) << " ";     
        else if (dynamic_cast< const OpDivergence * >(e.op()) != NULL)
          ss << " \\nabla \\cdot " << translator(lhs, true) << " ";     
        else if (dynamic_cast< const OpPartialDeriv * >(e.op()) != NULL)
        {
          const OpPartialDeriv * tmp = dynamic_cast< const OpPartialDeriv * >(e.op());
          viennamath::rt_variable<InterfaceType> var(tmp->op().id());
          ss << " \\frac{\\partial " << translator(lhs, true) << "}{\\partial " << translator(var) << "} ";
        }
        else if (dynamic_cast< const OpRuntimeIntegration * >(e.op()) != NULL)
        {
          const OpRuntimeIntegration * op_integral = dynamic_cast< const OpRuntimeIntegration * >(e.op());
          
          ss << " \\int_{ " << translator(op_integral->op().interval()) << " } ";
          ss << translator(lhs) << " ";
          ss << " \\: \\mathrm{d} " << translator(op_integral->op().variable()) << " ";
        }
        else if (dynamic_cast< const OpSymbolicIntegration * >(e.op()) != NULL)
        {
          const OpSymbolicIntegration * op_integral = dynamic_cast< const OpSymbolicIntegration * >(e.op());
          // integral:
          ss << " \\int_{\\Omega_{" << op_integral->op().interval().id() << "}} ";
          ss << translator(lhs) << " ";
          ss << " \\: \\mathrm{d} \\Omega ";
        }
        else
        {
          std::cout << "Operator not supported: " << e.op()->str() << std::endl;
          throw "Not supported!";
        }
        
        return ss.str();
      }
      
  }; 
  
  
  //
  // Constant
  //
  template <typename InterfaceType>
  class rt_latex_constant_processor : public rt_latex_processor_interface<InterfaceType>
  {
      typedef typename InterfaceType::numeric_type           NumericType;
      typedef viennamath::rt_constant<default_numeric_type, InterfaceType>   Constant;
    
    public:
      
      std::string process(InterfaceType const * ptr, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        if (dynamic_cast< const Constant * >(ptr) != NULL)
        {
          const Constant * temp = dynamic_cast< const Constant * >(ptr);
          return process_impl(*temp, use_parenthesis, translator);
        }
        
        return "";
      }
       
    private:

      std::string process_impl(Constant const & e, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        std::stringstream ss;
        ss << " " << static_cast<NumericType>(e) << " ";
        return ss.str();        
      }      
      
  }; 
  

  //
  // Variable
  //
  template <typename InterfaceType>
  class rt_latex_variable_processor : public rt_latex_processor_interface<InterfaceType>
  {
      typedef typename InterfaceType::numeric_type           NumericType;
      typedef viennamath::rt_variable<InterfaceType>                         Variable;
    
    public:
      
      std::string process(InterfaceType const * ptr, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        if (dynamic_cast< const Variable * >(ptr) != NULL)
        {
          const Variable * temp = dynamic_cast< const Variable * >(ptr);
          return process_impl(*temp, use_parenthesis, translator);
        }
        
        return "";
      }
       
      bool customize(InterfaceType const * ptr, std::string const & str)
      {
        if (dynamic_cast< const Variable * >(ptr) != NULL)
        {
          const Variable * temp = dynamic_cast< const Variable * >(ptr);
          variable_strings_[temp->id()] = str;
          return true;
        }
        return false;
      }
      
    private:

      std::string process_impl(Variable const & e, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        std::stringstream ss;

        std::map<id_type, std::string>::const_iterator it = variable_strings_.find(e.id());
        if (it != variable_strings_.end())
          ss << it->second;
        else
          ss << " x_{" << e.id() << "} ";
        
        return ss.str();        
      }      
      
      std::map<id_type, std::string>                            variable_strings_;
  }; 

  //
  // Function Symbol
  //
  template <typename InterfaceType>
  class rt_latex_function_symbol_processor : public rt_latex_processor_interface<InterfaceType>
  {
      typedef typename InterfaceType::numeric_type              NumericType;
      typedef viennamath::rt_function_symbol<InterfaceType>     FuncSymbol;
      typedef std::pair<id_type, id_type>           KeyType;
    
    public:
      
      std::string process(InterfaceType const * ptr, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        if (dynamic_cast< const FuncSymbol * >(ptr) != NULL)
        {
          const FuncSymbol * temp = dynamic_cast< const FuncSymbol * >(ptr);
          return process_impl(*temp, use_parenthesis, translator);
        }
        
        return "";
      }
       
      bool customize(InterfaceType const * ptr, std::string const & str)
      {
        if (dynamic_cast< const FuncSymbol * >(ptr) != NULL)
        {
          const FuncSymbol * temp = dynamic_cast< const FuncSymbol * >(ptr);
          KeyType key(temp->id(), temp->tag_id());
          function_symbol_strings_[key] = str;
          return true;
        }
        return false;
      }
      
    private:

      std::string process_impl(FuncSymbol const & e, bool use_parenthesis, rt_latex_translator<InterfaceType> const & translator) const 
      {
        std::stringstream ss;
        
        KeyType func_symb_id(e.id(), e.tag_id());
        std::map<KeyType, std::string>::const_iterator it = function_symbol_strings_.find(func_symb_id);
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
      
      std::map<KeyType, std::string>  function_symbol_strings_;
    
  }; 
  
  

}

#endif
