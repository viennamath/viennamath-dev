
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>

#include "viennamath/expression.hpp"
#include "viennamath/manipulation/eval.hpp"
#include "viennamath/manipulation/substitute.hpp"
#include "viennamath/manipulation/diff.hpp"

#include "viennamath/runtime/equation.hpp"
#include "viennamath/manipulation/integral.hpp"
#include "viennamath/weak_form.hpp"
#include "viennamath/manipulation/apply_coordinate_system.hpp"


using namespace viennamath;

//
// The strain tensor: eps_ij = 0.5 * (du_i/dx_j + du_j/dx_i)
// 
std::vector< expr<> > strain_tensor(std::vector< function_symbol<> > const & u)
{
  std::vector< expr<> > result(9);
  
  variable<> x(0);
  variable<> y(1);
  variable<> z(2);
  
  //first row:
  result[0] =        diff(u[0], x);
  result[1] = 0.5 * (diff(u[0], y) + diff(u[1], x));
  result[2] = 0.5 * (diff(u[0], z) + diff(u[2], x));
  
  //second row:
  result[3] = 0.5 * (diff(u[1], x) + diff(u[0], y));
  result[4] =        diff(u[1], y);
  result[5] = 0.5 * (diff(u[1], z) + diff(u[2], y));

  //third row:
  result[6] = 0.5 * (diff(u[2], x) + diff(u[0], z));
  result[7] = 0.5 * (diff(u[2], y) + diff(u[1], z));
  result[8] =        diff(u[2], z);

  std::cout << "strain_tensor end" << std::endl;
  return result;
}


//
// The stress tensor: sigma = 2 \mu eps + \lambda trace(eps) Id
// 
std::vector< expr<> > stress_tensor(std::vector< function_symbol<> > const & v)
{
  std::vector< expr<> > result(9);
  std::vector< expr<> > strain = strain_tensor(v);

  double mu = 1;
  
  //add 2 \mu eps:
  for (size_t i=0; i<9; ++i)
    result[i] = (2*mu) * strain[i];

  //add trace(eps) * Id:
  result[0] = (2*mu) * strain[0] + strain[0] + strain[4] + strain[8];
  result[4] = (2*mu) * strain[4] + strain[0] + strain[4] + strain[8];
  result[8] = (2*mu) * strain[8] + strain[0] + strain[4] + strain[8];
    
  std::cout << "stress_tensor end" << std::endl;
  return result;
}


expr<> tensor_reduce(std::vector< expr<> > lhs, std::vector< expr<> > rhs)
{
  expr<> ret = constant<double>(0);
  
  for (size_t i=0; i<rhs.size(); ++i)
    ret = ret + lhs[i] * rhs[i];
  
  return ret;
}



void print_entry(expr<> const & e, size_t test_index, size_t unknown_index)
{
    std::vector<viennamath::expr<> > basisfuncs(4);
    
    function_symbol<> u1(0, unknown_tag<>());   //an unknown function
    function_symbol<> u2(1, unknown_tag<>());   //an unknown function
    function_symbol<> u3(2, unknown_tag<>());   //an unknown function
    
    function_symbol<>    v1(0, test_tag<>());   //a test function (typical for FEM and FVM)
    function_symbol<>    v2(1, test_tag<>());   //a test function (typical for FEM and FVM)
    function_symbol<>    v3(2, test_tag<>());   //a test function (typical for FEM and FVM)
    
    expr<> result = e;
    //constant<default_numeric_type> zero(0);
  
    if (unknown_index != 0)
      result = viennamath::substitute(u1, 0, result);
    if (unknown_index != 1)
      result = viennamath::substitute(u2, 0, result);
    if (unknown_index != 2)
      result = viennamath::substitute(u3, 0, result);

    if (test_index != 0)
      result = viennamath::substitute(v1, 0, result);
    if (test_index != 1)
      result = viennamath::substitute(v2, 0, result);
    if (test_index != 2)
      result = viennamath::substitute(v3, 0, result);
    
    //while (result.get()->optimizable())
    for (size_t i=0; i<5; ++i)
    {
      std::cout << "optimizing binary_expr..." << std::endl;
      result = result.get()->optimize();
    }
    
    std::cout << result << std::endl;
}




int main()
{
  std::cout << "************************************************" << std::endl;
  std::cout << "*****     Demo for ViennaMath with FEM     *****" << std::endl;
  std::cout << "************************************************" << std::endl;

  function_symbol<> u1(0, unknown_tag<>());   //an unknown function
  function_symbol<> u2(1, unknown_tag<>());   //an unknown function
  function_symbol<> u3(2, unknown_tag<>());   //an unknown function

  function_symbol<> u_phi(42, unknown_tag<>());   //an unknown function

  std::vector< function_symbol<> > u(3);
  u[0] = u1;
  u[1] = u2;
  u[2] = u3;
  
  function_symbol<>    v1(0, test_tag<>());   //a test function (typical for FEM and FVM)
  function_symbol<>    v2(1, test_tag<>());   //a test function (typical for FEM and FVM)
  function_symbol<>    v3(2, test_tag<>());   //a test function (typical for FEM and FVM)
  
  function_symbol<>    v_phi(42, test_tag<>());   //a test function (typical for FEM and FVM)
  
  std::vector< function_symbol<> > v(3);
  v[0] = v1;
  v[1] = v2;
  v[2] = v3;
  
  variable<> x(0);
  variable<> y(1);
  variable<> z(2);

  std::cout << "-- Printing div(u): --" << std::endl;
  std::cout << diff(u1, x) << std::endl;
  std::cout << diff(u1, y) << std::endl;
  std::cout << diff(u1, z) << std::endl;

  std::cout << "-- Printing div(u): --" << std::endl;
  std::cout << div(u1) << std::endl;
  std::cout << "-- Printing div(u) with coordinate system applied in 1d, 2d and 3d: --" << std::endl;
  std::cout << apply_coordinate_system(cartesian<1>(), div(u1)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<2>(), div(u1)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<3>(), div(u1)) << std::endl;
  
  std::cout << "-- Printing div(v): --" << std::endl;
  std::cout << div(v2) << std::endl;
  
  std::cout << "-- Printing div(u) * div(v): --" << std::endl;
  std::cout << div(u1)*div(v2) << std::endl;
  std::cout << "-- Printing div(u) * div(v) with coordinate system applied in 1d, 2d and 3d: --" << std::endl;
  std::cout << apply_coordinate_system(cartesian<1>(), div(u1)*div(v1)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<2>(), div(u2)*div(v2)) << std::endl;
  std::cout << apply_coordinate_system(cartesian<3>(), div(u3)*div(v3)) << std::endl;
  

  //
  // Step 1: Define the classical Lame equation
  //             (lambda + mu) div(u) div(v) + mu grad(u):grad(v) = F
  // with force F set to 0.
  //
  viennamath::constant<double> lambda(1.0);
  viennamath::constant<double> mu(1.0);
  viennamath::constant<double> one_half(0.5);
  
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
  */                                              
  

  std::vector< expr<> > strain = strain_tensor(u);
  std::vector< expr<> > stress = stress_tensor(v);
  
  std::cout << "Strain: " << std::endl;
  for (size_t i=0; i<strain.size(); ++i)
    std::cout << strain[i] << std::endl;

  std::cout << "Stress: " << std::endl;
  for (size_t i=0; i<stress.size(); ++i)
    std::cout << stress[i] << std::endl;
  
  equation<> weak_form_lame = make_equation( 
                                 integral(Omega(), tensor_reduce( strain, stress ), symbolic_tag()),
                                 //=                                         
                                 0);
  
  
  //check entries in matrix:
  
  //first row:
  //expr<> lame_11_v = substitute(v1, v_phi, substitute(v2, 0, substitute(v3, 0, weak_form_lame.lhs())));
  //std::cout << substitute(u1, u_phi, substitute(u2, 0, substitute(u3, 0, lame_11_v))) << std::endl;
  
  std::cout << "Weak form of Lame equation: " << std::endl;
  std::cout << weak_form_lame << std::endl;
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "FEM-form: " << std::endl;
  print_entry(weak_form_lame.lhs(), 0, 0);  
  
  /*
  
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