// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/ParameterData.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using ParameterData = continuous::ParameterData;

std::vector< double > chunk();
void verifyChunk( const ParameterData&, const std::vector< double >& );
ParameterData makeDummyBlock();

SCENARIO( "ParameterData" ) {

  GIVEN( "valid data for a ParameterData instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< long > interpolants = {};
      std::vector< long > boundaries = {};
      std::vector< double > energies = { 1., 3., 5. };
      std::vector< double > values = { 2., 4., 6. };

      ParameterData chunk( std::move( boundaries ),
                           std::move( interpolants ),
                           std::move( energies ),
                           std::move( values ) );

      THEN( "a ParameterData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      ParameterData chunk( xss.begin(), xss.end() );

      THEN( "a ParameterData can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss  );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      ParameterData chunk( xss.begin(), xss.end() );
      ParameterData copy( chunk );

      THEN( "an ParameterData can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      ParameterData chunk( xss.begin(), xss.end() );
      ParameterData move( std::move( chunk ) );

      THEN( "an ParameterData can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      ParameterData chunk( xss.begin(), xss.end() );
      ParameterData copy = makeDummyBlock();
      copy = chunk;

      THEN( "an ParameterData can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      ParameterData chunk( xss.begin(), xss.end() );
      ParameterData move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an ParameterData can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 0, 3, 1., 3., 5., 2., 4., 6. };
}

void verifyChunk( const ParameterData& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 8 == chunk.length() );
  CHECK( "ParameterData" == chunk.name() );

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

  CHECK( 3 == chunk.NE() );
  CHECK( 3 == chunk.numberEnergyPoints() );

  CHECK( 3 == chunk.energies().size() );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 5., WithinRel( chunk.energies()[2] ) );

  CHECK( 3 == chunk.values().size() );
  CHECK_THAT( 2., WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 6., WithinRel( chunk.values()[2] ) );
}

ParameterData makeDummyBlock() {

  return { {}, {}, { 1., 2. }, { 3., 4. } };
}
