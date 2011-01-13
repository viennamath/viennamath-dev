/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_UNKNOWN_CPP
#define VIENNAMATH_UNKNOWN_CPP

#include "viennamath/constant.hpp"
#include "viennamath/vector.hpp"
#include "viennamath/op_tags.hpp"
#include "viennamath/expression_run_time.hpp"
#include "viennamath/expression_compile_time.hpp"

namespace viennamath
{
  /********** evaluation at STL vector types ***************/
  template <typename ScalarType,
            typename VectorType,
            long id>
  struct unknown_traits
  {
    typedef ScalarType   return_type;
    
    //per default, access id-th element;
    static return_type get(VectorType const & v)
    {
      return v[id];
    }
  };
  
  /********** evaluation at ViennaMath vector types ***************/
  template <typename vmath_vector, long id>
  struct type_by_index {};
  
  template <typename vmath_vector>
  struct type_by_index <vmath_vector, 0>
  {
    typedef typename vmath_vector::type_0   result_type; 
  };
  
  template <typename vmath_vector>
  struct type_by_index <vmath_vector, 1>
  {
    typedef typename vmath_vector::type_1   result_type; 
  };
  
  template <typename vmath_vector>
  struct type_by_index <vmath_vector, 2>
  {
    typedef typename vmath_vector::type_2   result_type; 
  };

  //vector_1:
  template <typename ScalarType,
            typename T0,
            long id>
  struct unknown_traits <ScalarType, 
                         vector_1<T0>, 
                         id>
  {
    typedef typename type_by_index<vector_1<T0>, id>::result_type   return_type;
    
    //per default, access id-th element;
    static return_type get(vector_1<T0> const & v)
    {
      return v[ct_index<id>()];
    }
  };
  
  //vector_2:
  template <typename ScalarType,
            typename T0, typename T1,
            long id>
  struct unknown_traits <ScalarType, 
                         vector_2<T0, T1>, 
                         id>
  {
    typedef typename type_by_index<vector_2<T0, T1>, id>::result_type   return_type;
    
    //per default, access id-th element;
    static return_type get(vector_2<T0, T1> const & v)
    {
      return v[ct_index<id>()];
    }
  };

  //vector_3:
  template <typename ScalarType,
            typename T0, typename T1, typename T2,
            long id>
  struct unknown_traits <ScalarType, 
                         vector_3<T0, T1, T2>, 
                         id>
  {
    typedef typename type_by_index<vector_3<T0, T1, T2>, id>::result_type   return_type;
    
    //per default, access id-th element;
    static return_type get(vector_3<T0, T1, T2> const & v)
    {
      return v[ct_index<id>()];
    }
  };

  

  /*********** evaluation of a run time constant: *****************/
  template <typename ScalarType>
  struct unknown_traits <ScalarType,
                         constant<ScalarType>,
                         0>
  {
    typedef viennamath::constant<ScalarType>   return_type;
    
    //per default, access id-th element;
    static return_type get(viennamath::constant<ScalarType> const & v)
    {
      return v;
    }
  };

  //guard: something like (x*y - z)(constant<double>(4)) is not allowed
  template <typename ScalarType, long id>
  struct unknown_traits <ScalarType, 
                         constant<ScalarType>,
                         id>
  {
    //try to provide a good compiler error message:
    typedef typename viennamath::constant<ScalarType>::ERROR_PROVIDED_NOT_ENOUGH_ARGUMENTS_TO_EXPRESSION   error_type;
    
    //providing a non-vector type is bogus -> force linker error!
  };
  
  /************* evaluation of a compile time constant *****************/
  template <typename ScalarType, long value_>
  struct unknown_traits <ScalarType, 
                         ct_constant<value_>,
                         0>
  {
    typedef viennamath::ct_constant<value_>   return_type;
    
    //per default, access id-th element;
    static return_type get(viennamath::ct_constant<value_> const & v)
    {
      return v;
    }
  };

  //guard: something like (x*y - z)(constant<long, ct_constant<4> >()) is not allowed
  template <typename ScalarType, long value_, long id>
  struct unknown_traits <ScalarType, 
                         ct_constant<value_>, 
                         id>
  {
    //try to provide a good compiler error message:
    typedef typename ct_constant<value_>::ERROR_PROVIDED_NOT_ENOUGH_ARGUMENTS_TO_EXPRESSION   error_type;
    
    //providing a non-vector type is bogus -> force linker error!
  };
  
  // further specialize unknown_traits::get() here as required.
  
  
  
  /** @brief Representation of an unknown (a variable). If the supplied argument is some vector type,
   *  a traits system accesses the id-th component
   * 
   * @tparam ScalarType        the underlying numerical type (typically float, double)
   * @tparam id                the component of the vector for which 'unknown' is evaluated
   */
  template <typename ScalarType, 
            unsigned long id /* see forwards.h for default argument */>
  struct unknown : public expression_interface
  {
    explicit unknown() {};

    std::ostream & operator<<(std::ostream & stream) const
    {
      stream << "unknown<" << id << ">";
      return stream;
    }

    /////////////////   Basic evaluation: //////////////////////////////////
    ScalarType operator()(ScalarType value) const
    {
      return value;
    }

    //Vector argument (can be of type std::vector
    template <typename VectorType>
    typename unknown_traits<ScalarType, VectorType, id>::return_type operator()(VectorType const & v) const
    {
      return unknown_traits<ScalarType, VectorType, id>::get(v);
    }
    
    //interface requirements:
    expression_interface * clone() const { return new unknown(); }
    expr eval(std::vector<double> const & v) const { return expr(constant<ScalarType>((*this)(v))); }
    std::string str() const
    {
      std::stringstream ss;
      ss << "unknown<" << id << ">";
      return ss.str();      
    }
    numeric_type unwrap() const
    {
      throw expression_not_unwrappable();
      return 0;
    }
      



    ////////////////// Operations //////////////////////////////
    
    //operator+
    template <typename LHS, typename OP, typename RHS>
    expression<unknown<ScalarType, id>,
               op_plus,
               expression<LHS, OP, RHS> >
    operator+(expression<LHS, OP, RHS> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_plus,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<unknown<ScalarType, id>,
               op_plus,
               unknown<OtherScalarType, other_id> >
    operator+(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_plus,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    expression<unknown<ScalarType, id>,
               op_plus,
               constant<OtherScalarType> >
    operator+(constant<OtherScalarType> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_plus,
                        constant<OtherScalarType> >(*this, other);
    }

    template <long value>
    expression<unknown<ScalarType, id>,
               op_plus,
               ct_constant<value> >
    operator+(ct_constant<value> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_plus,
                        ct_constant<value> >(*this, other);
    }


    //operator-
    template <typename LHS, typename OP, typename RHS>
    expression<unknown<ScalarType, id>,
               op_minus,
               expression<LHS, OP, RHS> >
    operator-(expression<LHS, OP, RHS> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_minus,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<unknown<ScalarType, id>,
               op_minus,
               unknown<OtherScalarType, other_id> >
    operator-(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_minus,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    expression<unknown<ScalarType, id>,
               op_minus,
               constant<OtherScalarType> >
    operator-(constant<OtherScalarType> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_minus,
                        constant<OtherScalarType> >(*this, other);
    }
    
    template <long value>
    expression<unknown<ScalarType, id>,
               op_minus,
               ct_constant<value> >
    operator-(ct_constant<value> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_minus,
                        ct_constant<value> >(*this, other);
    }


    //operator*
    template <typename LHS, typename OP, typename RHS>
    expression<unknown<ScalarType, id>,
               op_mult,
               expression<LHS, OP, RHS> >
    operator*(expression<LHS, OP, RHS> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_mult,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<unknown<ScalarType, id>,
               op_mult,
               unknown<OtherScalarType, other_id> >
    operator*(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_mult,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    expression<unknown<ScalarType, id>,
               op_mult,
               constant<OtherScalarType> >
    operator*(constant<OtherScalarType> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_mult,
                        constant<OtherScalarType> >(*this, other);
    }

    template <long value>
    expression<unknown<ScalarType, id>,
               op_mult,
               ct_constant<value> >
    operator*(ct_constant<value> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_mult,
                        ct_constant<value> >(*this, other);
    }


    //operator/
    template <typename LHS, typename OP, typename RHS>
    expression<unknown<ScalarType, id>,
               op_div,
               expression<LHS, OP, RHS> >
    operator/(expression<LHS, OP, RHS> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_div,
                        expression<LHS, OP, RHS> >(*this, other);
    }
    
    template <typename OtherScalarType, unsigned long other_id>
    expression<unknown<ScalarType, id>,
               op_div,
               unknown<OtherScalarType, other_id> >
    operator/(unknown<OtherScalarType, other_id> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_div,
                        unknown<OtherScalarType, other_id> >(*this, other);
    }

    template <typename OtherScalarType>
    expression<unknown<ScalarType, id>,
               op_div,
               constant<OtherScalarType> >
    operator/(constant<OtherScalarType> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_div,
                        constant<OtherScalarType> >(*this, other);
    }
    
    template <long value>
    expression<unknown<ScalarType, id>,
               op_div,
               ct_constant<value> >
    operator/(ct_constant<value> const & other) const
    {
      return expression<unknown<ScalarType, id>,
                        op_div,
                        ct_constant<value> >(*this, other);
    }
    
    

  };

  template <typename ScalarType, unsigned long id>
  std::ostream& operator<<(std::ostream & stream, unknown<ScalarType, id> const & u)
  {
    stream << "unknown<" << id << ">";
    return stream;
  }


}

#endif