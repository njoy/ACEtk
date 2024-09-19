// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedAngleEnergyDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedAngleEnergyDistribution = continuous::TabulatedAngleEnergyDistribution;
using TabulatedEnergyDistribution = continuous::TabulatedEnergyDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedAngleEnergyDistribution&, const std::vector< double >& );
TabulatedAngleEnergyDistribution makeDummyBlock();

SCENARIO( "TabulatedAngleEnergyDistribution" ) {

  GIVEN( "valid data for a TabulatedAngleEnergyDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int interpolation = 2;
      std::vector< TabulatedEnergyDistribution > distributions  = {

        TabulatedEnergyDistribution(
            -1., 2, { 1e-5, 1.0, 20.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
        TabulatedEnergyDistribution(
            1., 1, { 1e-3, 15.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } )
      };
      std::size_t locb = 21;

      TabulatedAngleEnergyDistribution chunk( 1.1,
                                              interpolation,
                                              std::move( distributions ),
                                              locb );

      THEN( "a TabulatedAngleEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedAngleEnergyDistribution chunk( 1.1, 21, xss.begin(), xss.end() );

      THEN( "a TabulatedAngleEnergyDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {             2,             2, -1.000000E+00,  1.000000E+00,
                      27,            38,             2,             3,
            1.000000E-05,  1.000000E+00,  2.000000E+01,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00,             1,             2,  1.000000E-03,
            1.500000E+01,  0.500000E+00,  0.500000E+00,  0.000000E+00,
            1.000000E+00 };
}

void verifyChunk( const TabulatedAngleEnergyDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 25 == chunk.length() );
  CHECK( "TabulatedAngleEnergyDistribution" == chunk.name() );

  CHECK_THAT( 1.1, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 2 == chunk.interpolation() );

  CHECK( 2 == chunk.NC() );
  CHECK( 2 == chunk.numberCosines() );
  CHECK( 2 == chunk.distributions().size() );

  CHECK( 2 == chunk.cosines().size() );
  CHECK_THAT( -1., WithinRel( chunk.cosines()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.cosines()[1] ) );

  CHECK_THAT( -1., WithinRel( chunk.cosine(1) ) );
  CHECK_THAT( 1., WithinRel( chunk.cosine(2) ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 38 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 38 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 18 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);
  CHECK_THAT( -1., WithinRel( data1.energyOrCosine() ) );
  CHECK( 2 == data1.interpolation() );
  CHECK( 3 == data1.numberOutgoingEnergies() );

  CHECK( 3 == data1.outgoingEnergies().size() );
  CHECK_THAT( 1e-5, WithinRel( data1.outgoingEnergies().front() ) );
  CHECK_THAT( 20., WithinRel( data1.outgoingEnergies().back() ) );

  CHECK( 3 == data1.pdf().size() );
  CHECK_THAT( .5, WithinRel( data1.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data1.pdf().back() ) );

  CHECK( 3 == data1.cdf().size() );
  CHECK_THAT( 0., WithinRel( data1.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data1.cdf().back() ) );

  auto data2 = chunk.distribution(2);
  CHECK_THAT( 1., WithinRel( data2.energyOrCosine() ) );
  CHECK( 1 == data2.interpolation() );
  CHECK( 2 == data2.numberOutgoingEnergies() );

  CHECK( 2 == data2.outgoingEnergies().size() );
  CHECK_THAT( 1e-3, WithinRel( data2.outgoingEnergies().front() ) );
  CHECK_THAT( 15., WithinRel( data2.outgoingEnergies().back() ) );

  CHECK( 2 == data2.pdf().size() );
  CHECK_THAT( .5, WithinRel( data2.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data2.pdf().back() ) );

  CHECK( 2 == data2.cdf().size() );
  CHECK_THAT( 0., WithinRel( data2.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data2.cdf().back() ) );
}
