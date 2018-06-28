#include "catch.hpp"

#include "ACEtk.hpp"

using namespace ACEtk::interpretation;

SCENARIO( "making regions" ){
  std::vector< double > INT{ 2, 3 };
  std::vector< double > NBT{ 3, 5 };
  std::vector< double > energies{ 1.0, 2.0, 3.0, 4.0, 5.0 };
  std::vector< double > nubar { 2.0, 2.1, 2.2, 2.3, 2.4 };

  GIVEN( "valid input values" ){
  }
} // SCENARIO
