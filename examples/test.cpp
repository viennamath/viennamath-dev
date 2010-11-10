

void testExpressions()
{
  typedef point_t< double,
                    ThreeDimensionsTag >                PointType;

  std::cout << std::endl;
  std::cout << "Expressions-Test:" << std::endl;
  std::cout << "-----------------" << std::endl;
  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;

  double in1, in2, in3;
//   std::cout << "Input point-coordinates: " << std::endl;
//   std::cin >> in1;
//   std::cin >> in2;
//   std::cin >> in3;

  ScalarExpression<1> _1_;
  ScalarExpression<2> _2_;
  ScalarExpression<3> _3_;
  ScalarExpression<4> _4_;
  ScalarExpression<5> _5_;
  ScalarExpression<10> _10_;
  std::cout << "4/5:" << (_4_ / _5_)() << std::endl;
  std::cout << "1 at (1/5, 2/5, 3/5):" << _1_(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;

  std::cout << "x at (1/5, 2/5, 3/5):" << var<'x'>()(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;

  std::cout << "y at (1/5, 2/5, 3/5):" << var<'y'>()(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;

  std::cout << "z at (1/5, 2/5, 3/5):" << var<'z'>()(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;


  PointType p_expr(0.3, 0.2, 0.1);
  //PointType p_expr(in1, in2, in3);
  std::cout << "Testing objects at (0.3, 0.2, 0.1):" << std::endl;
  std::cout << "1: " << _1_(p_expr) << std::endl;
  std::cout << "1: " << _1_(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "3/2: " << (_3_ / _2_)(p_expr) << std::endl;
  std::cout << "3/2: " << (_3_ / _2_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "x: " << ( x_ )(p_expr) << std::endl;
  std::cout << "x: " << ( x_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "(1-x)+(1-y): " << ( (_1_ - x_) + (_1_ - y_) )(p_expr) << std::endl;
  ( (_1_ - x_) + (_1_ - y_) ).print(); std::cout << std::endl;
  std::cout << "(1-x)+(1-y): " << ( (_1_ - x_) + (_1_ - y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "(1-x)-(1-y): " << ( (_1_ - x_) - (_1_ - y_) )(p_expr) << std::endl;
  std::cout << "(1-x)-(1-y): " << ( (_1_ - x_) - (_1_ - y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "(1-x)*(1-y): " << ( (_1_ - x_) * (_1_ - y_) )(p_expr) << std::endl;
  std::cout << "(1-x)*(1-y): " << ( (_1_ - x_) * (_1_ - y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "(1-x)/(1-y): " << ( (_1_ - x_) / (_1_ - y_) )(p_expr) << std::endl;
  std::cout << "(1-x)/(1-y): " << ( (_1_ - x_) / (_1_ - y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  #ifdef DIM3D
   std::cout << "(1-y-z): "<< ( _1_ - y_ - z_ )(p_expr) << std::endl;
   std::cout << "(1-y-z): "<< ( _1_ - y_ - z_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "(z+1): "<< ( z_ + _1_ )(p_expr) << std::endl;
   std::cout << "(z+1): "<< ( z_ + _1_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "(3*z): "<< ( _3_ * z_ )(p_expr) << std::endl;
   std::cout << "(3*z): "<< ( _3_ * z_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "(z*3): "<< ( z_ * _3_ )(p_expr) << std::endl;
   std::cout << "(z*3): "<< ( z_ * _3_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "(3.2 *(z+4)): "<< ( _3_ / (z_ + _4_) )(p_expr) << std::endl;
   std::cout << "(3.2 *(z+4)): "<< ( _3_ / (z_ + _4_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "((z+4) * 3.2): "<< ( (z_ + _4_) / 3.2 )(p_expr) << std::endl;
   std::cout << "((z+4) * 3.2): "<< ( (z_ + _4_) / 3.2 )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "4*(z*3): "<< ( _4_ * (z_ * _3_) )(p_expr) << std::endl;
   std::cout << "4*(z*3): "<< ( _4_ * (z_ * _3_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "(z*3)*4: "<< ( (z_ * _3_) * _4_ )(p_expr) << std::endl;
   std::cout << "(z*3)*4: "<< ( (z_ * _3_) * _4_ )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
   std::cout << "x*y*z: " << (x_ * y_ * z_)(p_expr) << std::endl;
   std::cout << "x*y*z: " << (x_ * y_ * z_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  #endif
  std::cout << "x * diff_y(y): "<< ( x_ * differentiate<'y'>(y_) )(p_expr) << std::endl;
  std::cout << "x * diff_y(y): "<< ( x_ * differentiate<'y'>(y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_x(diff_x(5.0)): "<< differentiate<'x'>(differentiate<'x'>(_5_))(p_expr) << std::endl;
  std::cout << "diff_x(diff_x(5.0)): "<< differentiate<'x'>(differentiate<'x'>(_5_))(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(y - 2.0): "<< ( differentiate<'y'>(y_ - _2_) )(p_expr) << std::endl;
  std::cout << "diff_y(y - 2.0): "<< ( differentiate<'y'>(y_ - _2_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(2.0 + 3.0 * y): "<< ( differentiate<'y'>(_3_ * y_ + _2_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 + 3.0 * y): "<< ( differentiate<'y'>(_3_ * y_ + _2_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(2.0 * y): "<< ( differentiate<'y'>(_2_ * y_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 * y): "<< ( differentiate<'y'>(_2_ * y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
/*  std::cout << "diff_y(2.0 / y): "<< ( differentiate_slow<'y'>(_2_ / y_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 / y): "<< ( differentiate_slow<'y'>(_2_ / y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl; */

  std::cout << "diff_y(2 * y^2): "<< differentiate<'y'>(_2_ * y_ * y_)(p_expr) << std::endl;
  std::cout << "diff_y(2 * y^2): "<< differentiate<'y'>(_2_ * y_ * y_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;

  std::cout << "diff_y(5.0 - 3.0 * x + 2.0 * y^2): "<< differentiate<'y'>(_5_ - _3_ * x_ + _2_ * y_ * y_)(p_expr) << std::endl;
  std::cout << "diff_y(5.0 - 3.0 * x + 2.0 * y^2): "<< differentiate<'y'>(_5_ - _3_ * x_ + _2_ * y_ * y_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;

  /*std::cout << "diff_x(2.0 * x * y / ( 2.0 + x)): " <<
                differentiate_slow<'x'>( (_2_ * x_ * y_)/(_2_ + x_) )(p_expr) << std::endl;
  std::cout << "diff_x(2.0 * x * y / ( 2.0 + x)): " <<
                differentiate_slow<'x'>( (_2_ * x_ * y_)/(_2_ + x_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;*/

//   std::cout << "Iterating over all vertices and evaluate 1-x-y: " << std::endl;
//   for (VertexIterator vit = seg.getVertexBegin();
//        vit != seg.getVertexEnd();
//        ++vit)
//   {
//     (*vit).print();
//     std::cout << std::endl;
//     std::cout << (ScalarExpression<double>(1.0) - x_ - y_)( (*vit).getPoint() ) << std::endl;
//   }

}

void testExpressionOptimizer()
{

  std::cout << std::endl;
  std::cout << "Expression-Optimizer-Test:" << std::endl;
  std::cout << "-----------------" << std::endl;
  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;

  ScalarExpression<1> _1_;
  ScalarExpression<2> _2_;
  ScalarExpression<3> _3_;
  ScalarExpression<4> _4_;
  ScalarExpression<5> _5_;
  ScalarExpression<10> _10_;

  std::cout << "diffy: 5 - 3x + 2y^2: ";
  differentiate_slow<'y'>(_5_ - _3_ * x_ + _2_ * y_ * y_).print(); std::cout << std::endl;

  std::cout << "diffx: 2xy / (2x): ";
//  differentiate_slow<'x'>((_2_ * x_ * y_)/(_2_ + x_)).print(); std::cout << std::endl;

  std::cout << "diffy: 2*y^2: ";
  differentiate_slow<'y'>(_2_ * y_ * y_).print(); std::cout << std::endl;

}

void testExpressionSubstitution()
{
  typedef point_t< double,
                    ThreeDimensionsTag >                PointType;

  std::cout << std::endl;
  std::cout << "Expression-Substitution-Test:" << std::endl;
  std::cout << "-----------------" << std::endl;
  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;

  ScalarExpression<-2> _m2_;
  ScalarExpression<-1> _m1_;
  ScalarExpression<0> _0_;
  ScalarExpression<1> _1_;
  ScalarExpression<2> _2_;
  ScalarExpression<3> _3_;
  ScalarExpression<4> _4_;
  ScalarExpression<5> _5_;
  ScalarExpression<10> _10_;

  std::cout << "replace (1-x) for y in x*y:";
  substitute(x_ * y_, y_, _1_ - x_).print(); std::cout << std::endl;

  std::cout << "replace x for y in y:";
  substitute(y_, y_, x_).print(); std::cout << std::endl;

  std::cout << "replace x for y in x*y:";
  substitute(x_ * y_, y_, x_).print(); std::cout << std::endl;

  std::cout << "replace 2 for y in x*y:";
  substitute(x_ * y_, y_, _2_).print(); std::cout << std::endl;

  std::cout << "replace _x_ for 2 in 2*2:";
  substitute(_2_ * _2_, _2_, x_).print(); std::cout << std::endl;

  std::cout << "replace _1_ for x in x*x*x:";
  substitute(x_ * x_ * x_, x_, _1_).print(); std::cout << std::endl;

  std::cout << "replace (1-x) for (1-y) in (1-x)*(1-y)*(1-z):";
  substitute((_1_ - x_) * (_1_ - y_) * (_1_ - z_), (_1_ - y_), _1_ - x_).print(); std::cout << std::endl;


  std::cout << "op-count for (1-x)*(1-y)*(1-z):" << std::endl;
  std::cout << "+: " << get_operation_count<op_plus>( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ) << std::endl;
  std::cout << "-: " << get_operation_count<op_minus>( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ) << std::endl;
  std::cout << "*: " << get_operation_count<op_mult>( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ) << std::endl;
  std::cout << "/: " << get_operation_count<op_div>( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ) << std::endl;

  std::cout << "op-count for 5x^2-3y+2z:" << std::endl;
  std::cout << "+: " << get_operation_count<op_plus>( _5_ * x_ * x_ - _3_ * y_ + _2_ * z_ ) << std::endl;
  std::cout << "-: " << get_operation_count<op_minus>( _5_ * x_ * x_ - _3_ * y_ + _2_ * z_ ) << std::endl;
  std::cout << "*: " << get_operation_count<op_mult>( _5_ * x_ * x_ - _3_ * y_ + _2_ * z_ ) << std::endl;
  std::cout << "/: " << get_operation_count<op_div>( _5_ * x_ * x_ - _3_ * y_ + _2_ * z_ ) << std::endl;

  std::cout << "op-count for (3x-4y)/z:" << std::endl;
  std::cout << "+: " << get_operation_count<op_plus>( (_3_ * x_ - _4_ * y_) / z_) << std::endl;
  std::cout << "-: " << get_operation_count<op_minus>( (_3_ * x_ - _4_ * y_) / z_) << std::endl;
  std::cout << "*: " << get_operation_count<op_mult>( (_3_ * x_ - _4_ * y_) / z_) << std::endl;
  std::cout << "/: " << get_operation_count<op_div>( (_3_ * x_ - _4_ * y_) / z_) << std::endl;

  std::cout << "op-count for xyz:" << std::endl;
  std::cout << "+: " << get_operation_count<op_plus>( x_*y_*z_ ) << std::endl;
  std::cout << "-: " << get_operation_count<op_minus>( x_*y_*z_ ) << std::endl;
  std::cout << "*: " << get_operation_count<op_mult>( x_*y_*z_ ) << std::endl;
  std::cout << "/: " << get_operation_count<op_div>( x_*y_*z_ ) << std::endl;

  std::cout << std::endl;
  std::cout << "Expandable-check for (1-x)*(1-y)*(1-z): "
            << isExpandable( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ) << std::endl;
  std::cout << "Expandable-check for 5x^2-3y+2z:: "
            << isExpandable( _5_ * x_ * x_ - _3_ * y_ + _2_ * z_ ) << std::endl;
  std::cout << "Expandable-check for (3x-4y)*z: "
            << isExpandable( (_3_ * x_ - _4_ * y_) * z_ ) << std::endl;
  std::cout << "Expandable-check for xyz: "
            << isExpandable( x_*y_*z_ ) << std::endl;

  std::cout << std::endl;
  std::cout << "Expand (1-x)*(1-y) by (1-z): ";
               expand_by_factor( (_1_ - x_) * (_1_ - y_) , (_1_ - z_) ).print(); std::cout << std::endl;
  std::cout << "Expand (3x-4y) by z: ";
               expand_by_factor( (_3_ * x_ - _4_ * y_), z_ ).print(); std::cout << std::endl;
  std::cout << "Expand xy by z: ";
               expand_by_factor( x_*y_, z_ ).print(); std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Expand (1-x)*(1-y)*(1-z): ";
               expand_expression( (_1_ - x_) * (_1_ - y_) * (_1_ - z_) ).print(); std::cout << std::endl;
  std::cout << "Expand (3x-4y) * z: ";
               expand_expression( (_3_ * x_ - _4_ * y_) * z_ ).print(); std::cout << std::endl;
  std::cout << "Expand xyz: ";
               expand_expression( x_*y_*z_ ).print(); std::cout << std::endl;
  std::cout << "Expand ((1-x)*y)*(1-z): ";
               expand_expression( ((_1_ - x_) * y_) * (_1_ - z_) ).print(); std::cout << std::endl;
  std::cout << "Expand (1-x)(1+x): ";
               expand_expression( (_1_ - x_) * (_1_ + x_) ).print(); std::cout << std::endl;
  std::cout << "Expand (1-x)*x*x*x*2: ";
               expand_expression( (_1_ - x_) * x_ * x_ * x_ * _2_ ).print(); std::cout << std::endl;
  std::cout << "Expand (1-x-y)*(1-x-y): ";
               expand_expression( (_1_ - x_ - y_) * (_1_ - x_ - y_ ) ).print(); std::cout << std::endl;

  std::cout << std::endl;
  std::cout << "Power of x in 5*x*y*z*x*3: " << power_of_variable(_5_ * x_ * y_ * z_ * x_ * _3_, x_) << std::endl;
  std::cout << std::endl;
  std::cout << "Power of y in 5*x*y*z*x*3: " << power_of_variable(_5_ * x_ * y_ * z_ * x_ * _3_, y_) << std::endl;
  std::cout << std::endl;
  std::cout << "Power of z in 5*x*y*z*x*3: " << power_of_variable(_5_ * x_ * y_ * z_ * x_ * _3_, z_) << std::endl;

  std::cout << std::endl;
  std::cout << "Integrate 1 over standard-triangle: " << 
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             _1_,
                                             x_),
                        y_)() << std::endl;

  std::cout << "Integrate x over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             x_,
                                             x_),
                        y_)() << std::endl;

  std::cout << "Integrate y over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             y_,
                                             y_),
                        y_)() << std::endl;

  std::cout << "Integrate x^2 over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             x_*x_,
                                             x_),
                        y_)() << std::endl;

  std::cout << "Integrate y^2 over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             y_ * y_,
                                             x_),
                        y_)() << std::endl;

  std::cout << "Integrate xy over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             x_ * y_,
                                             x_),
                        y_)() << std::endl;

  std::cout << "Integrate (1-x-y)*(1-x-y) over standard-triangle: " <<
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                                             (_1_ - x_ - y_) * (_1_ - x_ - y_),
                                             x_),
                        y_)() << std::endl;
/*
  std::cout << std::endl;
  std::cout << "Expression for laplace u:" << std::endl;
  expand_expression(
  substituteBasisfunctions( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                            basisfun<1, diff_y>() * basisfun<2, diff_y>(),
                            (_1_ - x_ - y_) * (_1_ - x_ - y_),
                            (_1_ - x_ - y_) * (_1_ - x_ - y_))
  ).print();
  std::cout << std::endl;
  std::cout << "Expression for laplace u (expanded), term dtdx00^2:" << std::endl;
  analytic_integration_extract_term<0,0>(
   expand_expression(
   substituteBasisfunctions( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                            basisfun<1, diff_y>() * basisfun<2, diff_y>(),
                            (_1_ - x_ - y_) * (_1_ - x_ - y_),
                            (_1_ - x_ - y_) * (_1_ - x_ - y_))
   )
  ).print();
  std::cout << std::endl;
  std::cout << std::endl;

  std::cout << "Differentiate (1-x-y)^2:" << std::endl;
  (differentiate<'x'>( (_1_ - x_ - y_) * (_1_ - x_ - y_) )).print(); std::cout << std::endl;
  */
  std::cout << "Differentiate (1-x-y)^2: " << std::endl;
  differentiate<'x'>((_1_ - x_ - y_)*(_1_ - x_ - y_)).print(); std::cout << std::endl;
  substituteBasisfunctions( basisfun<1, diff_x>() * basisfun<2, diff_x>(),
                            (_1_ - x_ - y_)*(_1_ - x_ - y_) ,
                            (_1_ - x_ - y_)*(_1_ - x_ - y_) ); std::cout << std::endl;


  std::cout << "Integrate (1-x-y)^4 over standard-triangle: " << std::endl;
  integrate_expression( _0_,
                        _1_,
                        integrate_expression(_0_,
                                             _1_ - y_,
                          substituteBasisfunctions( basisfun<1, diff_x>() * basisfun<2, diff_x>(),
                                                    (_1_ - x_ - y_)*(_1_ - x_ - y_) ,
                                                    (_1_ - x_ - y_)*(_1_ - x_ - y_) ),
                                             x_),
                        y_).print(); std::cout << std::endl;

/*
  std::cout << "Above expression after post-processing: " << std::endl;
  analytic_integration_triangle(
    expand_expression(
      substituteBasisfunctions( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                                basisfun<1, diff_y>() * basisfun<2, diff_y>(),
                                (_1_ - x_ - y_),
                                (_1_ - x_ - y_)
                              )
    )
  ).print();
  std::cout << std::endl;
  std::cout << std::endl;
*/

  std::cout << "Transforming laplace(u) to reference element:" << std::endl;
  transform_to_reference_element( gradient<TwoDimensionsTag, 1>() * gradient<TwoDimensionsTag, 2>() ).print(); std::cout << std::endl;
  std::cout << "Transforming laplace(u) to reference element, expanded:" << std::endl;
  expand_expression(
    transform_to_reference_element( gradient<TwoDimensionsTag, 1>() * gradient<TwoDimensionsTag, 2>() )
  ).print(); std::cout << std::endl;
  
  std::cout << "Integrate laplace(u) over reference element with bf1=(1-x-y), bf2=(1-x-y):" << std::endl;
  analytic_integration_triangle( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                                 basisfun<1, diff_y>() * basisfun<2, diff_y>(),
                                 (_1_ - x_ - y_),
                                 (_1_ - x_ - y_)).print();

  

  

//   //Test for differentiation:
//   std::cout << "Old differentiation of (1-x-y)(1-x-y)(1-x-y):" << std::endl;
//   expand_expression(
//     differentiate<'x'>( (_1_ - x_ - y_) * (_1_ - x_ - y_) * (_1_ - x_ - y_) )
//   ).print();
//   std::cout << std::endl;
// 
//   std::cout << "New differentiation of (1-x-y)(1-x-y)(1-x-y):" << std::endl;
//   expand_expression(
//     expression_differentiate<'x'>( (_1_ - x_ - y_) * (_1_ - x_ - y_) * (_1_ - x_ - y_) )
//   ).print();
//   std::cout << std::endl;

  std::cout << std::endl << std::endl;
  std::cout << "1/2: "; expression_optimize( _1_ - _1_ / _2_ ).print(); std::cout << std::endl;
  std::cout << "3/2: "; expression_optimize( _1_ - (_m1_ / _2_) ).print(); std::cout << std::endl;
  std::cout << "4/3: "; expression_optimize( _1_ - (_m1_ / _3_) ).print(); std::cout << std::endl;
  std::cout << "-1: "; expression_optimize( _m2_ - _m2_ / _2_ ).print(); std::cout << std::endl;
  std::cout << "2: "; expression_optimize( _4_ - _4_ / _2_ ).print(); std::cout << std::endl;

}


void testLogicals()
{

  typedef point_t< double,
                    ThreeDimensionsTag >              Point3d;

  typedef point_t< double,
                    TwoDimensionsTag >                Point2d;

  Point2d p2_1(0.1, 0.2);
  Point2d p2_2(0.0, 0.1);
  Point2d p2_3(0.0, 0.0);

  Point3d p3_1(1.0, 0.0, 0.5);
  Point3d p3_2(0.0, 1.0, 0.0);
  Point3d p3_3(0.234, 0.826, 0.917);
  Point3d p3_4(0.25, 0.25, 0.25);

  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;


  std::cout << " x == 0 || y == 0 : " << std::endl;
  std::cout << " p2_1: " << ( (x_ == 0.0) || (y_ == 0.0) )(p2_1) << std::endl;
  std::cout << " p2_2: " << ( (x_ == 0.0) || (y_ == 0.0) )(p2_2) << std::endl;
  std::cout << " p2_3: " << ( (x_ == 0.0) || (y_ == 0.0) )(p2_3) << std::endl;

  std::cout << " p3_1: " << ( (x_ == 0.0) || (y_ == 0.0) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ == 0.0) || (y_ == 0.0) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ == 0.0) || (y_ == 0.0) )(p3_3) << std::endl;

  std::cout << " x == 1 && y == 0 : " << std::endl;
  std::cout << " p2_1: " << ( (x_ == 1.0) && (y_ == 0.0) )(p2_1) << std::endl;
  std::cout << " p2_2: " << ( (x_ == 1.0) && (y_ == 0.0) )(p2_2) << std::endl;
  std::cout << " p2_3: " << ( (x_ == 1.0) && (y_ == 0.0) )(p2_3) << std::endl;

  std::cout << " p3_1: " << ( (x_ == 1.0) && (y_ == 0.0) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ == 1.0) && (y_ == 0.0) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ == 1.0) && (y_ == 0.0) )(p3_3) << std::endl;

  std::cout << " x == 0.234 && y == 0.826 && z == 0.917 : " << std::endl;
  std::cout << " p3_1: " << ( (x_ == 0.234) && (y_ == 0.826) && (z_ == 0.917) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ == 0.234) && (y_ == 0.826) && (z_ == 0.917) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ == 0.234) && (y_ == 0.826) && (z_ == 0.917) )(p3_3) << std::endl;

  std::cout << " x != 1.0 : " << std::endl;
  std::cout << " p2_1: " << ( (x_ != 1.0) )(p2_1) << std::endl;
  std::cout << " p2_2: " << ( (x_ != 1.0) )(p2_2) << std::endl;
  std::cout << " p2_3: " << ( (x_ != 1.0) )(p2_3) << std::endl;

  std::cout << " p3_1: " << ( (x_ != 1.0) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ != 1.0) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ != 1.0) )(p3_3) << std::endl;

  std::cout << " x + y != 1.0 : " << std::endl;
  std::cout << " p2_1: " << ( (x_ + y_ != 1.0) )(p2_1) << std::endl;
  std::cout << " p2_2: " << ( (x_ + y_ != 1.0) )(p2_2) << std::endl;
  std::cout << " p2_3: " << ( (x_ + y_ != 1.0) )(p2_3) << std::endl;

  std::cout << " p3_1: " << ( (x_ + y_ != 1.0) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ + y_ != 1.0) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ + y_ != 1.0) )(p3_3) << std::endl;

  std::cout << " x * y (* z) != 0.0 : " << std::endl;
  std::cout << " p2_1: " << ( (x_ * y_ != 0.0) )(p2_1) << std::endl;
  std::cout << " p2_2: " << ( (x_ * y_ != 0.0) )(p2_2) << std::endl;
  std::cout << " p2_3: " << ( (x_ * y_ != 0.0) )(p2_3) << std::endl;

  std::cout << " p3_1: " << ( (x_ * y_ * z_ != 0.0) )(p3_1) << std::endl;
  std::cout << " p3_2: " << ( (x_ * y_ * z_ != 0.0) )(p3_2) << std::endl;
  std::cout << " p3_3: " << ( (x_ * y_ * z_ != 0.0) )(p3_3) << std::endl;

}


void testMatrix()
{
  SparseMatrix<double> matrix( 5 );
  Vector<double> rhs( 5 );

  matrix(0,0) = 1;
  matrix(1,0) = 2; matrix(1,1) = 3;
  matrix(2,0) = 4; matrix(2,1) = 5; matrix(2,2) = 6;
                   matrix(3,1) = 7; matrix(3,2) = 8; matrix(3,3) = 9;
                                    matrix(4,2) = 10; matrix(4,3) = 11; matrix(4,4) = 12;
  rhs(0) = 1;
  rhs(1) = 1;
  rhs(2) = 2;
  rhs(3) = 3;
  rhs(4) = 4;

  (matrix * rhs).print();
  MatVecMatrix<double> mwm(matrix);
  (mwm * rhs).print();
  mwm.print();
}

/*
void testCompound()
{
  typedef point_t< double,
                    ThreeDimensionsTag >                PointType;

  std::cout << std::endl;
  std::cout << "Expression-Compound-Test:" << std::endl;
  std::cout << "-----------------" << std::endl;
  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;

  typedef Expression < double,
                        ScalarExpression<1>,
                        Expression< double,
                                    var<'x'>,
                                    var<'y'>,
                                    op_plus<double>
                                  >,
                        op_minus<double> >                        OneMinusXY;

  typedef Expression < double,
                        Expression< double,
                                    ScalarExpression<1>,
                                    var<'x'>,
                                    op_minus<double>
                                  >,
                        Expression< double,
                                    var<'y'>,
                                    var<'z'>,
                                    op_plus<double>
                                  >,
                        op_minus<double> >                        OneMinusXYZ;

  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, OneMinusXY, 0>     basic_compound_2d;
  CompoundExpression<1, 1, var<'x'>, 1, var<'y'>, 1, OneMinusXY, 0>     xy;
  CompoundExpression<1, 1, var<'x'>, 1, var<'y'>, 1, OneMinusXY, 1>     xy1_x_y;
  CompoundExpression<1, 1, var<'x'>, 2, var<'y'>, 2, OneMinusXY, 0>     x2y2;
  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, OneMinusXY, 1>     L1_x_yJ;
  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, OneMinusXY, 2>     L1_x_yJ2;
  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, OneMinusXY, 3>     L1_x_yJ3;

  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, var<'z'>, 0, OneMinusXYZ, 0>  basic_compound_3d;
  CompoundExpression<1, 1, var<'x'>, 0, var<'y'>, 0, var<'z'>, 0, OneMinusXYZ, 3>     L1_x_y_zJ3;


  ScalarExpression<-2> _m2_;
  ScalarExpression<-1> _m1_;
  ScalarExpression<0> _0_;
  ScalarExpression<1> _1_;
  ScalarExpression<2> _2_;
  ScalarExpression<3> _3_;
  ScalarExpression<4> _4_;
  ScalarExpression<5> _5_;
  ScalarExpression<10> _10_;

  PointType p(0.5, 2.0, 1.0);

  std::cout << "Evaluating at (0.5, 2.0, 1.0):" << std::endl;
  xy.print(); std::cout << ": " << xy(p) << std::endl;
  xy1_x_y.print(); std::cout << ": " << xy1_x_y(p) << std::endl;
  x2y2.print(); std::cout << ": " << x2y2(p) << std::endl;
  L1_x_yJ2.print(); std::cout << ": " << L1_x_yJ2(p) << std::endl;

  std::cout << "Optimizing expressions: " << std::endl;
  ( x_ * xy * y_).print(); std::cout << " <-> "; expression_optimize( x_ * xy * y_ ).print();std::cout << std::endl; 
  ( _4_ * x2y2 ).print(); std::cout << " <-> "; expression_optimize( _4_ * x2y2 ).print(); std::cout << std::endl;
  ( x2y2 * _4_ ).print(); std::cout << " <-> "; expression_optimize( x2y2 * _4_ ).print(); std::cout << std::endl;
  ( x2y2 * xy ).print(); std::cout << " <-> "; expression_optimize( x2y2 * xy ).print(); std::cout << std::endl;


  std::cout << "Differentiating: " << std::endl;
  xy.print(); std::cout << ": d/dx -> "; differentiate_slowslow<'x'>(xy).print(); std::cout << std::endl;
  xy.print(); std::cout << ": d/dy -> "; differentiate<'y'>(xy).print(); std::cout << std::endl;
  x2y2.print(); std::cout << ": d/dx -> "; differentiate<'x'>(x2y2).print(); std::cout << std::endl;
  x2y2.print(); std::cout << ": d/dy -> "; differentiate<'y'>(x2y2).print(); std::cout << std::endl;
  xy1_x_y.print(); std::cout << ": d/dx -> "; differentiate<'x'>(xy1_x_y).print(); std::cout << std::endl;
  xy1_x_y.print(); std::cout << ": d/dy -> "; differentiate<'y'>(xy1_x_y).print(); std::cout << std::endl; 
  L1_x_yJ2.print(); std::cout << ": d/dx -> "; differentiate<'x'>(L1_x_yJ2).print(); std::cout << std::endl;
  L1_x_yJ2.print(); std::cout << ": d/dy -> "; differentiate<'y'>(L1_x_yJ2).print(); std::cout << std::endl;

  std::cout << "Integration: " << std::endl;

  std::cout << "Transforming laplace(u) to reference element, expanded:" << std::endl;
  expand_expression(
    transform_to_reference_element( gradient<TwoDimensionsTag, 1>() * gradient<TwoDimensionsTag, 2>() )
  ).print(); std::cout << std::endl;

  std::cout << "Analytic integration, old scheme:" << std::endl;
//   analytic_integration_triangle( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
//                                  basisfun<1, diff_y>() * basisfun<2, diff_y>(),
//                                  (_1_ - x_ - y_),
//                                  (_1_ - x_ - y_)).print(); std::cout << std::endl;

  std::cout << "Analytic integration triangle, compounded" << std::endl;
  analytic_integration_triangle( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                                 basisfun<1, diff_y>() * basisfun<2, diff_y>(),
                                 L1_x_yJ3,
                                 L1_x_yJ3).print(); std::cout << std::endl;

  std::cout << "Analytic integration tetrahedron, compounded" << std::endl;
  analytic_integration_tetrahedron( basisfun<1, diff_x>() * basisfun<2, diff_x>() + 
                                 basisfun<1, diff_y>() * basisfun<2, diff_y>() + 
                                 basisfun<1, diff_z>() * basisfun<2, diff_z>() ,
                                 L1_x_y_zJ3,
                                 L1_x_y_zJ3).print(); std::cout << std::endl;

  std::cout << "Make compound:" << std::endl;
  (x_ * y_ * (_1_ - x_ - y_) * (_1_ - x_ - y_)).print(); std::cout << " -> ";
  expression_to_compound( x_ * y_ * (_1_ - x_ - y_) * (_1_ - x_ - y_), basic_compound_2d ).print(); std::cout << std::endl;

  (x_ * y_ * z_ * ((_1_ - x_) - (y_ + z_)) * ((_1_ - x_) - (y_ + z_))).print(); std::cout << " -> ";
  expression_to_compound( x_ * y_ * z_ * ((_1_ - x_) - (y_ + z_)) * ((_1_ - x_) - (y_ + z_)), basic_compound_3d ).print(); std::cout << std::endl;

} */

void testAnaIntegration()
{
  var<'x'> x_;
  var<'y'> y_;
  var<'z'> z_;

  ScalarExpression<-2> _m2_;
  ScalarExpression<-1> _m1_;
  ScalarExpression<0> _0_;
  ScalarExpression<1> _1_;
  ScalarExpression<2> _2_;
  ScalarExpression<3> _3_;
  ScalarExpression<4> _4_;
  ScalarExpression<5> _5_;
  ScalarExpression<10> _10_;

    transform_to_reference_triangle<UniformTriangleSegment>
      (basisfun<1, diff_x>() * basisfun<2, diff_x>() + basisfun<1, diff_y>() * basisfun<2, diff_y>()).print(); std::cout << std::endl;

  analytic_integration_triangle(
    transform_to_reference_triangle<UniformTriangleSegment>
      (basisfun<1, diff_x>() * basisfun<2, diff_x>() + basisfun<1, diff_y>() * basisfun<2, diff_y>()),
    (_1_ - (x_ + y_)),
    (_1_ - (x_ + y_))
    ).print(); std::cout << std::endl;

  DT_DX_EXTRACTOR< Expression< double,
                               Expression < double,
                                            basisfun<1, diff_x>,
                                            dt_dx<1,0>,
                                            op_mult<double>
                                          >,
                               Expression < double,
                                            basisfun<2, diff_y>,
                                            dt_dx<0,1>,
                                            op_mult<double>
                                          >,
                               op_mult<double>
                              >
                 >::ResultType().print(); std::cout << std::endl;


}


template <typename Equation>
void testAssembly2(Equation const & equ)
{
    typedef typename ASSEMBLY_GET_FIRST_INT_DOMAIN<Equation>::ResultType  IntDomain;
    std::cout << "Integration Domain: "; IntDomain().print(); std::cout << std::endl;

    typedef typename ASSEMBLY_EXTRACT_DOMAIN<Equation, IntDomain>::ResultType   CurrentEquation;
    std::cout << "Current equation: "; CurrentEquation().print(); std::cout << std::endl;

    typedef typename ASSEMBLY_REARRANGER<CurrentEquation>::ResultType     ReorderedEquation;
    std::cout << "Reordered equation: "; ReorderedEquation().print(); std::cout << std::endl;

    typedef typename ASSEMBLY_REMOVE_DOMAIN<Equation, IntDomain>::ResultType   RemainingEquation;
    std::cout << "Remaining equation: "; RemainingEquation().print(); std::cout << std::endl;

    testAssembly2( RemainingEquation() );
}

template <>
void testAssembly2<EmptyEquation>(EmptyEquation const & equ){};

void testAssembly()
{
  typedef gradient<TwoDimensionsTag, 1>              grad_v;
  typedef gradient<TwoDimensionsTag, 2>              grad_u;
  typedef basisfun<1>                                  v;
  typedef basisfun<2>                                  u;

  OrderSevenIntegrationTag          inttag;

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( grad_v() * grad_u(), inttag)
              = 
            integral<Omega>( v(), inttag )
  );

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( v(), inttag )
              = 
            integral<Omega>( grad_v() * grad_u(), inttag)
  );

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( v(), inttag )
              = 
            integral<Omega>( grad_v() * grad_u(), inttag) - integral<Omega>( u() * v(), inttag )
  );

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( v(), inttag ) - integral<Gamma<1> >( v(), inttag )
              = 
            integral<Omega>( grad_v() * grad_u(), inttag) - integral<Omega>( u() * v(), inttag )
  );

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( grad_v() * grad_u(), inttag) - integral<Omega>( v(), inttag ) - integral<Gamma<1> >( v(), inttag ) + integral<Omega>( u() * v(), inttag )
              = 
             ScalarExpression<0>()
  );

  std::cout << "-----------------------------" << std::endl;
  testAssembly2( 
            integral<Omega>( grad_v() * grad_u(), inttag) - integral<Omega>( v(), inttag ) - integral<Gamma<1> >( v(), inttag ) + integral<Omega>( u() * v(), inttag )
              = 
            integral<Gamma<2> >( v(), inttag )
  );


}

