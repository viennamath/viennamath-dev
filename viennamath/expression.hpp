/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                 ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMath base directory
======================================================================= */



#ifndef VIENNAMATH_EXPRESSION_HPP
#define VIENNAMATH_EXPRESSION_HPP

#include "viennamath/forwards.h"
#include "viennamath/compiletime/promote_traits.hpp"

#include "viennamath/compiletime/ct_vector.hpp"
#include "viennamath/compiletime/ct_constant.hpp"
//#include "viennamath/compiletime/ct_function_symbol.hpp"
#include "viennamath/compiletime/ct_variable.hpp"
#include "viennamath/compiletime/ct_expr.hpp"

#include "viennamath/runtime/variable.hpp"
#include "viennamath/runtime/binary_expression.hpp"
#include "viennamath/runtime/binary_operators.hpp"
#include "viennamath/runtime/unary_expression.hpp"
#include "viennamath/runtime/unary_operators.hpp"
#include "viennamath/runtime/expr.hpp"

#include "viennamath/manipulation/unary_operators_manipulation.hpp"
#include "viennamath/manipulation/binary_operators_manipulation.hpp"

#include "viennamath/compiletime/operations/ct_ct.hpp"
#include "viennamath/compiletime/operations/ct_constant.hpp"
#include "viennamath/compiletime/operations/ct_variable.hpp"
#include "viennamath/compiletime/operations/ct_expr.hpp"

#include "viennamath/runtime/operations/rt_rt.hpp"
#include "viennamath/runtime/operations/binary_expression.hpp"
#include "viennamath/runtime/operations/unary_expression.hpp"
#include "viennamath/runtime/operations/expr.hpp"
#include "viennamath/runtime/operations/constant.hpp"
#include "viennamath/runtime/operations/variable.hpp"
#include "viennamath/operations/function_symbol_operations.hpp"


#endif