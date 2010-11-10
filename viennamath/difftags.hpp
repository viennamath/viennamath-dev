/* =======================================================================
   Copyright (c) 2010, Institute for Microelectronics, TU Vienna.
   http://www.iue.tuwien.ac.at
                             -----------------
                     ViennaMath - Symbolic and Numeric Math in C++
                             -----------------

   authors:    Karl Rupp                          rupp@iue.tuwien.ac.at

   license:    MIT (X11), see file LICENSE in the ViennaMesh base directory
======================================================================= */

/********* included by expressions.h *************************/

 template <long coord, typename EXPR = diff_none>
 struct diff;

 //helper for type lists:
 template <typename EVAL_MODIFIER, typename EXPR>
 struct DIFF_TYPELIST;

 template <long coord, typename EVAL_MODIFIER, typename EXPR>
 struct DIFF_TYPELIST< diff<coord, EVAL_MODIFIER>, EXPR >
 {
   typedef typename EXPRESSION_DIFFERENTIATE<var<coord>,
                                     typename DIFF_TYPELIST<EVAL_MODIFIER, EXPR>::ResultType
                                               >::ResultType           ResultType;
 };

 template <typename EXPR>
 struct DIFF_TYPELIST< diff_none, EXPR >
 {
   typedef EXPR           ResultType;
 };

 //helper for type erasure
 template <typename diff_expr>
 struct DIFF_EVALUATION_HELPER
 {};

 template <>
 struct DIFF_EVALUATION_HELPER< diff_none >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf(p);
  };
 };

 //first order derivative:
 template <>
 struct DIFF_EVALUATION_HELPER< diff<0, diff_none> >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_0(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<1, diff_none> >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_1(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<2, diff_none> >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_2(p);
  };
 };

 //second order derivatives:
 template <>
 struct DIFF_EVALUATION_HELPER< diff<0, diff<0, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_00(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<0, diff<1, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_01(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<0, diff<2, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_02(p);
  };
 };

 template <>
 struct DIFF_EVALUATION_HELPER< diff<1, diff<0, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_10(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<1, diff<1, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_11(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<1, diff<2, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_12(p);
  };
 };

 template <>
 struct DIFF_EVALUATION_HELPER< diff<2, diff<0, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_20(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<2, diff<1, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_21(p);
  };
 };
 template <>
 struct DIFF_EVALUATION_HELPER< diff<2, diff<2, diff_none> > >
 {
  template <typename BasisFun, typename Point>
  static typename Point::CoordType apply(BasisFun const & bf, const Point & p)
  {
    return bf.diff_22(p);
  };
 };

 //no third derivatives for the moment...


 template <long dim, typename DIFF_TAG, typename EVAL_MODIFIER = diff_none, long current_index = 0>
 struct DIFF_TRANSFORMER;

 template <long dim, long coord, typename DIFF_TAG, typename EVAL_MODIFIER, long current_index>
 struct DIFF_TRANSFORMER<dim, diff<coord, DIFF_TAG>, EVAL_MODIFIER, current_index>
 {
    template <typename CellType, typename BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType & cell, BasisFun const & bf, const Point & p)
    { 
      return DIFF_TRANSFORMER<dim, DIFF_TAG, diff<current_index, EVAL_MODIFIER> >::apply(cell, bf, p) * cell.get_dt_dx(current_index, coord)
        + DIFF_TRANSFORMER<dim, diff<coord, DIFF_TAG>, EVAL_MODIFIER, current_index + 1 >::apply(cell, bf, p);
    }
 };

 template <long dim, long coord, typename DIFF_TAG, typename EVAL_MODIFIER>
 struct DIFF_TRANSFORMER<dim, diff<coord, DIFF_TAG>, EVAL_MODIFIER, dim>
 {
    template <typename CellType, typename BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType & cell, BasisFun const & bf, const Point & p)
    { 
      return 0.0;
    }
 };

 template <long dim, typename EVAL_MODIFIER, long current_index>
 struct DIFF_TRANSFORMER<dim, diff_none, EVAL_MODIFIER, current_index>
 {
    //type erasure:
    template <typename CellType, template <typename> class BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType & cell, BasisFun<Point> const & bf, const Point & p)
    { 
      return DIFF_EVALUATION_HELPER<EVAL_MODIFIER>::apply(bf, p);
    }

    //type list:
    template <typename CellType, typename BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType & cell, BasisFun const & bf, const Point & p)
    { 
      typedef typename DIFF_TYPELIST<EVAL_MODIFIER, BasisFun>::ResultType    DiffType;
      return DiffType()(p);
    }

 };


 template <long coord, typename EXPR>
 struct diff
 {
    template <typename CellType, typename BasisFun, typename Point>
    static typename CellType::Configuration::CoordType apply(CellType & cell, BasisFun const & bf, const Point & p)
    { 
      return DIFF_TRANSFORMER<Point::DimensionsTag::dim,
                               diff<coord, EXPR> >::apply(cell, bf, p);
    }

    static void print()
    {
      std::cout << "diff<" << coord << ", "; EXPR::print(); std::cout << ">";
    }
 };


