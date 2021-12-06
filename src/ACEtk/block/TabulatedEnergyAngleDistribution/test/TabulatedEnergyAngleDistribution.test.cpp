#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/TabulatedEnergyAngleDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedEnergyAngleDistribution = block::TabulatedEnergyAngleDistribution;
using TabulatedAngularDistribution = block::TabulatedAngularDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedEnergyAngleDistribution& );

SCENARIO( "TabulatedEnergyAngleDistribution" ) {

  GIVEN( "valid data for a TabulatedEnergyAngleDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< TabulatedAngularDistribution > distributions  = {

        TabulatedAngularDistribution(
            2.1, 2, { -1.0, 0.0, 1.0 }, { 0.5, 0.5, 0.5 }, { 0.0, 0.5, 1.0 } ),
        TabulatedAngularDistribution(
            20., 1, { -1.0, 1.0 }, { 0.5, 0.5 }, { 0.0, 1.0 } )
      };
      std::size_t locb = 21;

      TabulatedEnergyAngleDistribution chunk( 1.1,
                                                      std::move( distributions ),
                                                      locb );

      THEN( "a TabulatedEnergyAngleDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      TabulatedEnergyAngleDistribution chunk( 1.1, 21,
                                                      xss.begin(), xss.end() );

      THEN( "a TabulatedEnergyAngleDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {             0,             2,  2.100000E+00,  2.000000E+01,
                      27,            38,             2,             3,
           -1.000000E+00,  0.000000E+00,  1.000000E+00,  0.500000E+00,
            0.500000E+00,  0.500000E+00,  0.000000E+00,  0.500000E+00,
            1.000000E+00,             1,             2, -1.000000E+00,
            1.000000E+00,  0.500000E+00,  0.500000E+00,  0.000000E+00,
            1.000000E+00 };
}

void verifyChunk( const TabulatedEnergyAngleDistribution& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 25 == chunk.length() );
  CHECK( "TabulatedEnergyAngleDistribution" == chunk.name() );

  CHECK( 1.1 == Approx( chunk.incidentEnergy() ) );

  CHECK( 0 == chunk.interpolationData().NB() );
  CHECK( 0 == chunk.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == chunk.interpolationData().INT().size() );
  CHECK( 0 == chunk.interpolationData().interpolants().size() );
  CHECK( 0 == chunk.interpolationData().NBT().size() );
  CHECK( 0 == chunk.interpolationData().boundaries().size() );

  CHECK( 0 == chunk.NB() );
  CHECK( 0 == chunk.numberInterpolationRegions() );
  CHECK( 0 == chunk.INT().size() );
  CHECK( 0 == chunk.interpolants().size() );
  CHECK( 0 == chunk.NBT().size() );
  CHECK( 0 == chunk.boundaries().size() );

  CHECK( 2 == chunk.NE() );
  CHECK( 2 == chunk.numberOutgoingEnergies() );

  CHECK( 2 == chunk.outgoingEnergies().size() );
  CHECK( 2.1 == Approx( chunk.outgoingEnergies()[0] ) );
  CHECK( 20. == Approx( chunk.outgoingEnergies()[1] ) );

  CHECK( 2.1 == Approx( chunk.outgoingEnergy(1) ) );
  CHECK( 20. == Approx( chunk.outgoingEnergy(2) ) );

  CHECK( 27 == chunk.LOCC(1) );
  CHECK( 38 == chunk.LOCC(2) );
  CHECK( 27 == chunk.distributionLocator(1) );
  CHECK( 38 == chunk.distributionLocator(2) );

  CHECK( 7 == chunk.relativeDistributionLocator(1) );
  CHECK( 18 == chunk.relativeDistributionLocator(2) );

  auto data1 = chunk.distribution(1);
  CHECK( 2.1 == Approx( data1.energy() ) );
  CHECK( 2 == data1.interpolation() );
  CHECK( 3 == data1.numberCosines() );

  CHECK( 3 == data1.cosines().size() );
  CHECK( -1. == Approx( data1.cosines().front() ) );
  CHECK( +1. == Approx( data1.cosines().back() ) );

  CHECK( 3 == data1.pdf().size() );
  CHECK( .5 == Approx( data1.pdf().front() ) );
  CHECK( .5 == Approx( data1.pdf().back() ) );

  CHECK( 3 == data1.cdf().size() );
  CHECK( 0. == Approx( data1.cdf().front() ) );
  CHECK( 1. == Approx( data1.cdf().back() ) );

  auto data2 = chunk.distribution(2);
  CHECK( 20 == Approx( data2.energy() ) );
  CHECK( 1 == data2.interpolation() );
  CHECK( 2 == data2.numberCosines() );

  CHECK( 2 == data2.cosines().size() );
  CHECK( -1. == Approx( data2.cosines().front() ) );
  CHECK( +1. == Approx( data2.cosines().back() ) );

  CHECK( 2 == data2.pdf().size() );
  CHECK( .5 == Approx( data2.pdf().front() ) );
  CHECK( .5 == Approx( data2.pdf().back() ) );

  CHECK( 2 == data2.cdf().size() );
  CHECK( 0. == Approx( data2.cdf().front() ) );
  CHECK( 1. == Approx( data2.cdf().back() ) );
}
