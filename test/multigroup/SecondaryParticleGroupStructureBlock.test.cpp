// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/multigroup/SecondaryParticleGroupStructureBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleGroupStructureBlock = multigroup::SecondaryParticleGroupStructureBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleGroupStructureBlock&, const std::vector< double >& );

SCENARIO( "SecondaryParticleGroupStructureBlock" ) {

  GIVEN( "valid data for a SecondaryParticleGroupStructureBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > centers = {

          1.450000000000E+01,  8.500000000000E+00,  7.500000000000E+00,  6.500000000000E+00,  
          5.500000000000E+00,  4.500000000000E+00,  3.500000000000E+00,  2.500000000000E+00,  
          1.500000000000E+00,  7.500000000000E-01,  3.000000000000E-01,  5.500000000000E-02
      };
      
      std::vector< double > widths = {

         11,                   1,                   1,                   1, 
          1,                   1,                   1,                   1,
          1,  5.000000000000E-01,  4.000000000000E-01,  9.000000000000E-02  
      };

      SecondaryParticleGroupStructureBlock chunk( std::move( centers ),
                                        std::move( widths ));

      THEN( "a SecondaryParticleGroupStructureBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 12 );

      THEN( "a SecondaryParticleGroupStructureBlock can be constructed and members can "
            "be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      SecondaryParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 12 );
      SecondaryParticleGroupStructureBlock copy( chunk );

      THEN( "an SecondaryParticleGroupStructureBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      SecondaryParticleGroupStructureBlock chunk( xss.begin(), xss.end(), 12 );
      SecondaryParticleGroupStructureBlock move( std::move( chunk ) );

      THEN( "an SecondaryParticleGroupStructureBlock can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

  1.450000000000E+01,  8.500000000000E+00,  7.500000000000E+00,  6.500000000000E+00,  
  5.500000000000E+00,  4.500000000000E+00,  3.500000000000E+00,  2.500000000000E+00,  
  1.500000000000E+00,  7.500000000000E-01,  3.000000000000E-01,  5.500000000000E-02,
                  11,                   1,                   1,                   1, 
                   1,                   1,                   1,                   1,
                   1,  5.000000000000E-01,  4.000000000000E-01,  9.000000000000E-02  
  };
}

void verifyChunk( const SecondaryParticleGroupStructureBlock& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 12*2 == chunk.length() );
  CHECK( "ERG2" == chunk.name() );

  CHECK( 12*2 == chunk.XSS().size() );

  CHECK( 12 == chunk.NERG() );
  CHECK( 12 == chunk.numberEnergyGroups() );
  CHECK( 12 == chunk.groupMeans().size() );
  CHECK( 12 == chunk.groupWidths().size() );

  CHECK_THAT( 14.5, WithinRel( chunk.groupMeans().front() ) );
  CHECK_THAT( 0.055, WithinRel( chunk.groupMeans().back() ) );
  CHECK_THAT( 11, WithinRel( chunk.groupWidths().front() ) );
  CHECK_THAT( 0.09, WithinRel( chunk.groupWidths().back() ) );
}
