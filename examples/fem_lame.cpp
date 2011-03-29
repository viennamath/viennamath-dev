
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/eval.hpp"
#include "viennamath/substitute.hpp"
#include "viennamath/diff.hpp"

#include "viennamath/equation.hpp"
#include "viennamath/integral.hpp"
#include "viennamath/weak_form.hpp"
#include "viennamath/apply_coordinate_system.hpp"


using namespace viennamath;

int main()
{
  std::cout << "************************************************" << std::endl;
  std::cout << "*****     Demo for ViennaMath with FEM     *****" << std::endl;
  std::cout << "************************************************" << std::endl;

  function_symbol<unknown_tag<0> > u;   //an unknown function
  
  /*typedef function_symbol<unknown_tag<0> >   U0;
  typedef function_symbol<unknown_tag<1> >   U1;
  typedef function_symbol<unknown_tag<2> >   U2;
  ct_vector_3<U0, U1, U2> u = make_vector(U0(), U1(), U2()); */
  
  function_symbol<test_tag<0> >    v;   //a test function (typical for FEM and FVM)
  /*typedef function_symbol<test_tag<0> >   V0;
  typedef function_symbol<test_tag<1> >   V1;
  typedef function_symbol<test_tag<2> >   V2;
  ct_vector_3<V0, V1, V2> v = make_vector(V0(), V1(), V2());*/
  
  std::cout << "-- Printing div(u): --" << std::endl;
  std::cout << div(u) << std::endl;
  std::cout << "-- Printing div(u) with coordinate system applied in 1d, 2d and 3d: --" << std::endl;
  std::cout << apply_coordinate_system(cartesian<1>(), div(u)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<2>(), div(u)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<3>(), div(u)) << std::endl;
  
  std::cout << "-- Printing div(v): --" << std::endl;
  std::cout << div(v) << std::endl;
  
  std::cout << "-- Printing div(u) * div(v): --" << std::endl;
  std::cout << div(u)*div(v) << std::endl;
  std::cout << "-- Printing div(u) * div(v) with coordinate system applied in 1d, 2d and 3d: --" << std::endl;
  std::cout << apply_coordinate_system(cartesian<1>(), div(u)*div(v)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<2>(), div(u)*div(v)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<3>(), div(u)*div(v)) << std::endl;
  

  //
  // Step 1: Define the classical Lame equation
  //             (lambda + mu) div(u) div(v) + mu grad(u):grad(v) = F
  // with force F set to 0.
  //
  viennamath::constant<double> lambda(1.0);
  viennamath::constant<double> mu(1.0);
  /*
  equation<> strong_form = make_equation( (lambda + mu) * grad(div(u)) + mu * laplace(u), 0);
  std::cout << "Strong (classical) form of equation:" << std::endl;
  std::cout << "  " << strong_form << std::endl;
  
  //
  // Step 2: Specify weak form:
  //
  equation<> weak_form_general = make_equation( (lambda + mu) * integral(Omega(), div(u) * div(v), symbolic_tag())
                                                 +        mu  * integral(Omega(), tensor_add(grad(u), grad(v)), symbolic_tag()),
                                                // = 
                                                0 );
  
  std::cout << "General weak form: " << std::endl;
  std::cout << "  " << weak_form_general << std::endl;

  // Step 3: The final form of the gradient still depends on the underlying coordinate system.
  //         We thus transform the general weak form to cartesian coordinate systems.
  //
  //         Example in 2d:  grad(u) * grad(v)  is transformed to u_x * v_x + u_y * v_y
  //
  equation<> weak_form_1d = apply_coordinate_system(cartesian<1>(), weak_form_general);
  std::cout << "Weak form in 1d:" << std::endl;
  std::cout << "  " << weak_form_1d << std::endl;
  
  equation<> weak_form_2d = apply_coordinate_system(cartesian<2>(), weak_form_general);
  std::cout << "Weak form in 2d:" << std::endl;
  std::cout << "  " << weak_form_2d << std::endl;
  
  equation<> weak_form_3d = apply_coordinate_system(cartesian<3>(), weak_form_general);
  std::cout << "Weak form in 3d:" << std::endl;
  std::cout << "  " << weak_form_3d << std::endl;
  */
  //
  // That's it! Everything else is left to ViennaFEM
  //
  std::cout << "************************************************" << std::endl;
  std::cout << "*****     TEST COMPLETED SUCCESSFULLY!     *****" << std::endl;
  std::cout << "************************************************" << std::endl;
  
  return EXIT_SUCCESS;
}