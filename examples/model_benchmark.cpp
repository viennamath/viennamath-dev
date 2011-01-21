
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "viennamath/expression.hpp"
#include "viennamath/eval.hpp"
#include "viennamath/substitute.hpp"

#include "examples/benchmark-utils.hpp"

#define BENCHMARK_SIZE   1000000


void print_stats(double result, double elapsed)
{
  std::cout << "|" << std::endl;
  std::cout << "|   * result: " << result << std::endl;
  std::cout << "|   * time: " << elapsed << std::endl;
  std::cout << "|" << std::endl;
  std::cout << std::endl;
}

int main()
{
  Timer timer;
  double elapsed;
  double result = 0;
  double x_ref = 2.0;
  double T_ref = 300;
  double kb = 1.61;
  double voltage = 3.0;
  double prefactor = 2.0;
  double eps = 8.854e-12;
  
  double mult;
  
  //
  // First step: disable precomputations by the compiler for naive implementation
  // If not specified at runtime, compiler might detect voltage and prefactor to be constants and precompute results
  std::cout << "Enter '1': ";
  std::cin >> mult;
  voltage *= mult;
  prefactor *= mult;
  T_ref *= mult;
  kb *= mult;
  
  std::cout << "--------- Naive (standard) implementation --------- " << std::endl;
  
  //the reference implementation:
  timer.start();
  for (int i=0; i<BENCHMARK_SIZE; ++i)
    result += (T_ref * eps * x_ref * ::exp( prefactor * voltage / (kb * T_ref) ) );
  elapsed = timer.get();

  
  print_stats(result, elapsed);
  
  
  std::cout << "--------- Hand tuned implementation (best possible, but will never be achieved within a simulator) --------- " << std::endl;
  
  //the reference implementation:
  result = 0;
  timer.start();
  for (int i=0; i<BENCHMARK_SIZE; ++i)
    result += 2.6894024e-9 * x_ref;
  elapsed = timer.get();
  
  print_stats(result, elapsed);

  
  
  std::cout << "--------- ViennaMath (runtime) --------- " << std::endl;
  
  //ViennaMath:
  viennamath::unknown<double, 0>  x;
  viennamath::unknown<double, 1>  T;
  viennamath::constant<double>    value_for_T(300.0);
  viennamath::binary_expr e = (T * eps * x * viennamath::exp( prefactor * voltage / (kb * T) ) );
  std::cout << "Expression before substitution: " << e << std::endl;
  viennamath::binary_expr e_opt = viennamath::substitute(T, value_for_T, e);
  std::cout << "Expression after substitution: " << e_opt << std::endl;
  result = 0;
  timer.start();
  for (int i=0; i<BENCHMARK_SIZE; ++i)
    result += viennamath::eval(e_opt, 2.0);
  elapsed = timer.get();
  
  print_stats(result, elapsed);
  
  
  std::cout << "--------- ViennaMath (compiletime) --------- " << std::endl;
  std::cout << "|" << std::endl;
  std::cout << "|  * (not possible in this case)" << std::endl;
  std::cout << "|" << std::endl;
  
  
  return EXIT_SUCCESS;
}