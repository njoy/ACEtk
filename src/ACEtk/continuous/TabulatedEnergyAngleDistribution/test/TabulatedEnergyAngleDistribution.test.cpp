// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedEnergyAngleDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedEnergyAngleDistribution = continuous::TabulatedEnergyAngleDistribution;
using TabulatedAngularDistributionWithProbability = continuous::TabulatedAngularDistributionWithProbability;

std::vector< double > chunk();
void verifyChunk( const TabulatedEnergyAngleDistribution&, const std::vector< double >& );
TabulatedEnergyAngleDistribution makeDummyBlock();

SCENARIO( "TabulatedEnergyAngleDistribution" ) {

  GIVEN( "valid data for a TabulatedEnergyAngleDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      unsigned int interpolation = 2;
      std::vector< TabulatedAngularDistributionWithProbability > distributions  = {

        TabulatedAngularDistributionWithProbability(
            2.1, 0.5, 0.5, 2, { -1.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
        TabulatedAngularDistributionWithProbability(
            20., 0.5, 1., 1, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } )
      };
      std::size_t locb = 21;

      TabulatedEnergyAngleDistribution chunk( 1.1,
                                              interpolation,
                                              std::move( distributions ),
                                              locb );

      THEN( "a TabulatedEnergyAngleDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedEnergyAngleDistribution chunk( 1.1, 21, xss.begin(), xss.end() );

      THEN( "a TabulatedEnergyAngleDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {             2,             2,  2.100000E+00,  2.000000E+01,
            0.500000E+00,  0.500000E+00,  0.500000E+00,  1.000000E+00,
                      31,            42,             2,             3,
           -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00,             1,             2, -1.000000E+00,
            1.000000E+00,  0.500000E+00,  0.500000E+00,  0.000000E+00,
            1.000000E+00 };
}

void verifyChunk( const TabulatedEnergyAngleDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 29 == chunk.length() );
  CHECK( "TabulatedEnergyAngleDistribution" == chunk.name() );

  CHECK_THAT( 1.1, WithinRel( chunk.incidentEnergy() ) );

  CHECK( 2 == chunk.interpolation() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberOutgoingEnergies() );
  CHECK( 2 == chunk.distributions().size() );

  CHECK( 2 == chunk.outgoingEnergies().size() );
  CHECK_THAT( 2.1, WithinRel( chunk.outgoingEnergies()[0] ) );
  CHECK_THAT( 20., WithinRel( chunk.outgoingEnergies()[1] ) );

  CHECK( 2 == chunk.pdf().size() );
  CHECK_THAT( 0.5, WithinRel( chunk.pdf()[0] ) );
  CHECK_THAT( 0.5, WithinRel( chunk.pdf()[1] ) );

  CHECK( 2 == chunk.cdf().size() );
  CHECK_THAT( 0.5, WithinRel( chunk.cdf()[0] ) );
  CHECK_THAT( 1.0, WithinRel( chunk.cdf()[1] ) );

  CHECK_THAT( 2.1, WithinRel( chunk.outgoingEnergy(1) ) );
  CHECK_THAT( 20., WithinRel( chunk.outgoingEnergy(2) ) );

  CHECK_THAT( 0.5, WithinRel( chunk.probability(1) ) );
  CHECK_THAT( 0.5, WithinRel( chunk.probability(2) ) );

  CHECK_THAT( 0.5, WithinRel( chunk.cumulativeProbability(1) ) );
  CHECK_THAT( 1.0, WithinRel( chunk.cumulativeProbability(2) ) );

  CHECK( 31 == chunk.LOCC(1) );
  CHECK( 42 == chunk.LOCC(2) );
  CHECK( 31 == chunk.distributionLocator(1) );
  CHECK( 42 == chunk.distributionLocator(2) );

  CHECK( 11 == chunk.relativeDistributionLocator(1) );
  CHECK( 22 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);
  CHECK_THAT( 2.1, WithinRel( data1.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data1.probability() ) );
  CHECK_THAT( 0.5, WithinRel( data1.cumulativeProbability() ) );
  CHECK( 2 == data1.interpolation() );
  CHECK( 3 == data1.numberCosines() );

  CHECK( 3 == data1.cosines().size() );
  CHECK_THAT( -1., WithinRel( data1.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data1.cosines().back() ) );

  CHECK( 3 == data1.pdf().size() );
  CHECK_THAT( .5, WithinRel( data1.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data1.pdf().back() ) );

  CHECK( 3 == data1.cdf().size() );
  CHECK_THAT( 0., WithinRel( data1.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data1.cdf().back() ) );

  auto data2 = chunk.distribution(2);
  CHECK_THAT( 20, WithinRel( data2.energy() ) );
  CHECK_THAT( 0.5, WithinRel( data1.probability() ) );
  CHECK_THAT( 0.5, WithinRel( data1.cumulativeProbability() ) );
  CHECK( 1 == data2.interpolation() );
  CHECK( 2 == data2.numberCosines() );

  CHECK( 2 == data2.cosines().size() );
  CHECK_THAT( -1., WithinRel( data2.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( data2.cosines().back() ) );

  CHECK( 2 == data2.pdf().size() );
  CHECK_THAT( .5, WithinRel( data2.pdf().front() ) );
  CHECK_THAT( .5, WithinRel( data2.pdf().back() ) );

  CHECK( 2 == data2.cdf().size() );
  CHECK_THAT( 0., WithinRel( data2.cdf().front() ) );
  CHECK_THAT( 1., WithinRel( data2.cdf().back() ) );
}
