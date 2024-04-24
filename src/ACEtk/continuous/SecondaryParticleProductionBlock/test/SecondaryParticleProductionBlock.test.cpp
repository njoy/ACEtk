// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/SecondaryParticleProductionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using SecondaryParticleProductionBlock = continuous::SecondaryParticleProductionBlock;

std::vector< double > chunk();
void verifyChunk( const SecondaryParticleProductionBlock& );

SCENARIO( "SecondaryParticleProductionBlock" ) {

  GIVEN( "valid data for a SecondaryParticleProductionBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::size_t index = 1;
      std::vector< double > production = {

        1.71740100000E+01, 1.21438600000E+01, 2.72235400000E+02
      };
      std::vector< double > heating = {

        3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05
      };

      SecondaryParticleProductionBlock chunk( index,
                                              std::move( production ),
                                              std::move( heating ) );

      THEN( "a SecondaryParticleProductionBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      SecondaryParticleProductionBlock chunk( xss.begin(), xss.end() );

      THEN( "a SecondaryParticleProductionBlock can be constructed and members "
            "can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

                    1,
                    3, 1.71740100000E+01, 1.21438600000E+01, 2.72235400000E+02,
    3.63894900000E-05, 3.67662300000E-05, 3.70168600000E-05 };
}

void verifyChunk( const SecondaryParticleProductionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "HPD" == chunk.name() );

  CHECK( 1 == chunk.energyIndex() );
  CHECK( 3 == chunk.numberValues() );

  CHECK( 3 == chunk.totalProduction().size() );
  CHECK_THAT( 17.17401, WithinRel( chunk.totalProduction().front() ) );
  CHECK_THAT( 272.2354, WithinRel( chunk.totalProduction().back() ) );

  CHECK( 3 == chunk.heating().size() );
  CHECK_THAT( 3.63894900000E-05, WithinRel( chunk.heating().front() ) );
  CHECK_THAT( 3.70168600000E-05, WithinRel( chunk.heating().back() ) );
}
