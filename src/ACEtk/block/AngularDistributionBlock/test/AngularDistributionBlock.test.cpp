#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/block/AngularDistributionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using AngularDistributionBlock = block::AngularDistributionBlock;
using AngularDistributionData = block::AngularDistributionData;
using FullyIsotropicDistribution = block::FullyIsotropicDistribution;
using DistributionGivenElsewhere = block::DistributionGivenElsewhere;
using DistributionData = AngularDistributionBlock::DistributionData;

std::vector< double > chunk();
void verifyChunk( const AngularDistributionBlock& );

SCENARIO( "AngularDistributionBlock" ) {

  GIVEN( "valid data for a AngularDistributionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

//        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

//        auto xss_chunk = chunk.XSS();
//        for ( unsigned int i = 0; i < chunk.length(); ++i ) {
//
//          CHECK( xss[i] == Approx( xss_chunk[i] ) );
//        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      AngularDistributionBlock chunk( xss.begin(), xss.begin() + 4, xss.end(), 4 );

      THEN( "a AngularDistributionBlock can be constructed and members can be tested" ) {

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

  // 4 reactions:
  //   - first and last reaction have data given
  //   - second one is given elsewhere
  //   - third one is fully isotropic
  // the given data:
  //   - for reaction 1 : 2 incident energies
  //   - for reaction 4 : 3 incident energies
  return {                 1,                 -1,                  0,                 25,
                           2,  1.00000000000E-11,  2.00000000000E+01,                 -6,
                         -14,                  2,                  2, -1.00000000000E+00,
           1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
           1.00000000000E+00,                  2,                  3, -1.00000000000E+00,
           0.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
           5.00000000000E-01,  0.00000000000E+00,  5.00000000000E-01,  1.00000000000E+00,
                           3,  1.00000000000E-11,  1.00000000000E+00,  2.00000000000E+01,
                         -32,                  0,                -43,                  2,
                           3, -1.00000000000E+00,  0.00000000000E+00,  1.00000000000E+00,
           5.00000000000E-01,  5.00000000000E-01,  5.00000000000E-01,  0.00000000000E+00,
           5.00000000000E-01,  1.00000000000E+00,                  2,                  2,
          -1.00000000000E+00,  1.00000000000E+00,  5.00000000000E-01,  5.00000000000E-01,
           0.00000000000E+00,  1.00000000000E+00 };
}

void verifyChunk( const AngularDistributionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 54 == chunk.length() );
  CHECK( "AND" == chunk.name() );

  CHECK( 4 == chunk.NTR() );
  CHECK( 4 == chunk.numberReactions() );

}
