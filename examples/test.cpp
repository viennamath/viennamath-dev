


/*
void testExpressions()
{
  typedef point_t< double,
                    ThreeDimensionsTag >                PointType;

  std::cout << std::endl;
  std::cout << "Expressions-Test:" << std::endl;
  std::cout << "-----------------" << std::endl;
  var<0> x_;
  var<1> y_;
  var<2> z_;

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

  std::cout << "x at (1/5, 2/5, 3/5):" << var<0>()(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;

  std::cout << "y at (1/5, 2/5, 3/5):" << var<1>()(
                  makeExpressionList3(
                    (_1_ / _5_),
                    (_2_ / _5_),
                    (_3_ / _5_) )
               ) << std::endl;

  std::cout << "z at (1/5, 2/5, 3/5):" << var<2>()(
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
  std::cout << "x * diff_y(y): "<< ( x_ * differentiate<1>(y_) )(p_expr) << std::endl;
  std::cout << "x * diff_y(y): "<< ( x_ * differentiate<1>(y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_x(diff_x(5.0)): "<< differentiate<0>(differentiate<0>(_5_))(p_expr) << std::endl;
  std::cout << "diff_x(diff_x(5.0)): "<< differentiate<0>(differentiate<0>(_5_))(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(y - 2.0): "<< ( differentiate<1>(y_ - _2_) )(p_expr) << std::endl;
  std::cout << "diff_y(y - 2.0): "<< ( differentiate<1>(y_ - _2_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(2.0 + 3.0 * y): "<< ( differentiate<1>(_3_ * y_ + _2_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 + 3.0 * y): "<< ( differentiate<1>(_3_ * y_ + _2_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(2.0 * y): "<< ( differentiate<1>(_2_ * y_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 * y): "<< ( differentiate<1>(_2_ * y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;
  std::cout << "diff_y(2.0 / y): "<< ( differentiate_slow<'y'>(_2_ / y_) )(p_expr) << std::endl;
  std::cout << "diff_y(2.0 / y): "<< ( differentiate_slow<'y'>(_2_ / y_) )(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;

  std::cout << "diff_y(2 * y^2): "<< differentiate<1>(_2_ * y_ * y_)(p_expr) << std::endl;
  std::cout << "diff_y(2 * y^2): "<< differentiate<1>(_2_ * y_ * y_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;

  std::cout << "diff_y(5.0 - 3.0 * x + 2.0 * y^2): "<< differentiate<1>(_5_ - _3_ * x_ + _2_ * y_ * y_)(p_expr) << std::endl;
  std::cout << "diff_y(5.0 - 3.0 * x + 2.0 * y^2): "<< differentiate<1>(_5_ - _3_ * x_ + _2_ * y_ * y_)(makeExpressionList3(
                    (_3_ / _10_),
                    (_2_ / _10_),
                    (_1_ / _10_) )) << std::endl;


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
  differentiate_slow<1>(_5_ - _3_ * x_ + _2_ * y_ * y_).print(); std::cout << std::endl;

  std::cout << "diffx: 2xy / (2x): ";
//  differentiate_slow<'x'>((_2_ * x_ * y_)/(_2_ + x_)).print(); std::cout << std::endl;

  std::cout << "diffy: 2*y^2: ";
  differentiate_slow<1>(_2_ * y_ * y_).print(); std::cout << std::endl;

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

} */

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "viennamath/unknown.hpp"
#include "viennamath/constant.hpp"


int main()
{
  viennamath::unknown<double, 0> x;
  viennamath::unknown<double, 1> y;
  viennamath::constant<double> c4(4.0);
  viennamath::constant<long, 8> c8;
  
  std::vector<double> p(2);
  p[0] = 1;
  p[1] = 2;
  
  std::cout << "x(" << p[0] << "," << p[1] << ") = " << x(p) << std::endl;
  std::cout << "y(" << p[0] << "," << p[1] << ") = " << y(p) << std::endl;

  
  std::cout << "c4(" << p[0] << "," << p[1] << ") = " << c4(p) << std::endl;
  std::cout << "c8(" << p[0] << "," << p[1] << ") = " << c8(p) << std::endl;
  
  return EXIT_SUCCESS;
}