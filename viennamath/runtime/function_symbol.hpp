/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_FUNCTION_SYMBOL_HPP
#define VIENNAMATH_FUNCTION_SYMBOL_HPP

#include <ostream>
#include <sstream>
#include "viennamath/forwards.h"
#include "viennamath/compiletime/ct_function_symbol.hpp"
#include "viennamath/runtime/expression_interface.hpp"

namespace viennamath
{

  /** @brief A function symbol. Can be used for unknown functions, test functions, etc. Cannot be evaluated, but substituted with an evaluable object 
   *
   * @tparam Tag    A tag class that is typically used to distinguish between different function symbols. Tag requirements: 'static std::string str();' which returns an identification string
   */
  template <typename InterfaceType>
  class function_symbol : public InterfaceType
  {
      typedef function_symbol<InterfaceType>     self_type;
    public:
      typedef typename InterfaceType::numeric_type      numeric_type;
      typedef InterfaceType                             interface_type;
      
      template <typename Tag>
      function_symbol(id_type i, Tag const & t) : id_(i), tag_id_(Tag::tag_id()) {}

      function_symbol(id_type i, id_type t) : id_(i), tag_id_(t) {}

      function_symbol() : id_(0), tag_id_(unknown_tag<>::tag_id()) {}
      
      id_type id() const { return id_; }
      id_type tag_id() const { return tag_id_; }

      //interface requirements:
      InterfaceType * clone() const { return new self_type(id_, tag_id_); }
      numeric_type eval(std::vector<double> const & v) const { throw "Cannot evaluate function_symbol!"; return 0; }
      numeric_type eval(numeric_type v) const { throw "Cannot evaluate function_symbol!"; return 0; }
      std::string deep_str() const
      {
        std::stringstream ss;
        ss << "function_symbol<";
        if (tag_id_ == unknown_tag<>::tag_id())
          ss << unknown_tag<>::str() << ">";
        else if (tag_id_ == test_tag<>::tag_id())
          ss << test_tag<>::str() << ">";
        else
          ss << "invalid>";
        
        return ss.str();      
      }
      numeric_type unwrap() const { throw "Cannot evaluate function_symbol to a number!"; }
      
      InterfaceType * substitute(const InterfaceType * e,
                                 const InterfaceType * repl) const
      {
        if (equal(e))
            return repl->clone();
        
        return clone();
      };    
      
      bool deep_equal(const InterfaceType * other) const
      {
        const self_type * ptr = dynamic_cast< const self_type *>(other);
        if (ptr != NULL)
        {
          if (ptr->id() == id_ && ptr->tag_id_ == tag_id_)
            return true;
        }
        return false;
      }
      
      bool shallow_equal(const InterfaceType * other) const
      {
        return dynamic_cast< const self_type * >(other) != NULL;
      }
      
      InterfaceType * diff(const InterfaceType * diff_var) const
      {
        //this code should not be reached, because function_symbol is symbolically differentiated at a higher level
        throw "Cannot differentiate function_symbol!";
        return NULL;
      }
      
    private:
      id_type id_;
      id_type tag_id_;
  };

  
  
  template <typename Tag, typename InterfaceType>
  std::ostream& operator<<(std::ostream & stream, function_symbol<InterfaceType> const & v)
  {
    stream << v.str();
    return stream;
  }
  
  
  
}

#endif