// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedEnergyDistribution = continuous::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedEnergyDistribution&, const std::vector< double >& );
TabulatedEnergyDistribution makeDummyBlock();

SCENARIO( "TabulatedEnergyDistribution" ) {

  GIVEN( "valid data for a TabulatedEnergyDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double value = 2.1;
      int interpolation = 2;
      std::size_t discrete = 3;
      std::vector< double > cosines = { 1e-11, 1.0, 20.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };

      TabulatedEnergyDistribution chunk( value, interpolation,
                                         std::move( cosines ),
                                         std::move( pdf ),
                                         std::move( cdf ),
                                         discrete );

      THEN( "a TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      double value = 2.1;
      TabulatedEnergyDistribution chunk( value, xss.begin(), xss.end() );

      THEN( "a TabulatedEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {                32,                  3,  1.00000000000E-11,  1.00000000000E+00,
           2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const TabulatedEnergyDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 11 == chunk.length() );
  CHECK( "TabulatedEnergyDistribution" == chunk.name() );

  CHECK_THAT( 2.1, WithinRel( chunk.energyOrCosine() ) );
  CHECK( 2 == chunk.interpolation() );
  CHECK( 3 == chunk.numberDiscretePhotonLines() );
  CHECK( 3 == chunk.numberOutgoingEnergies() );

  CHECK( 3 == chunk.outgoingEnergies().size() );
  CHECK_THAT( 1e-11, WithinRel( chunk.outgoingEnergies().front() ) );
  CHECK_THAT( 20., WithinRel( chunk.outgoingEnergies().back() ) );

  CHECK( 3 == chunk.pdf().size() );
  CHECK_THAT( .5, WithinRel( chunk.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( chunk.pdf().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK_THAT( 0., WithinRel( chunk.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( chunk.cdf().back() ) );
}
