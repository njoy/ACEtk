// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/thermal/DiscreteCosines.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using DiscreteCosines = thermal::DiscreteCosines;

std::vector< double > chunk();
void verifyChunk( const DiscreteCosines&, const std::vector< double >& );
DiscreteCosines makeDummyBlock();

SCENARIO( "DiscreteCosines" ) {

  GIVEN( "valid data for a DiscreteCosines instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 2.1;
      std::vector< double > cosines = {

        -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.3, -0.2, -0.1, 0.0,
        0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5,
        0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.925, 0.95,
        0.9625, 0.975, 1.0
      };

      DiscreteCosines chunk( energy, std::move( cosines ) );

      THEN( "a DiscreteCosines can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      DiscreteCosines chunk( 33, xss.begin(), xss.end() );

      THEN( "a DiscreteCosines can be constructed "
            "and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      DiscreteCosines chunk( 33, xss.begin(), xss.end() );
      DiscreteCosines copy( chunk );

      THEN( "an DiscreteCosines can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      DiscreteCosines chunk( 33, xss.begin(), xss.end() );
      DiscreteCosines move( std::move( chunk ) );

      THEN( "an DiscreteCosines can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      DiscreteCosines chunk( 33, xss.begin(), xss.end() );
      DiscreteCosines copy = makeDummyBlock();
      copy = chunk;

      THEN( "an DiscreteCosines can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      DiscreteCosines chunk( 33, xss.begin(), xss.end() );
      DiscreteCosines move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an DiscreteCosines can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {

     2.10000000000E+00,
    -1.00000000000E+00, -0.90000000000E+00, -0.80000000000E+00, -0.70000000000E+00,
    -0.60000000000E+00, -0.50000000000E+00, -0.30000000000E+00, -0.20000000000E+00,
    -0.10000000000E+00,  0.00000000000E+00,  0.05000000000E+00,  0.10000000000E+00,
     0.15000000000E+00,  0.20000000000E+00,  0.25000000000E+00,  0.30000000000E+00,
     0.35000000000E+00,  0.40000000000E+00,  0.45000000000E+00,  0.50000000000E+00,
     0.55000000000E+00,  0.60000000000E+00,  0.65000000000E+00,  0.70000000000E+00,
     0.75000000000E+00,  0.80000000000E+00,  0.85000000000E+00,  0.90000000000E+00,
     0.92500000000E+00,  0.95000000000E+00,  0.96250000000E+00,  0.97500000000E+00,
     1.00000000000E+00
  };
}

void verifyChunk( const DiscreteCosines& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 34 == chunk.length() );
  CHECK( "DiscreteCosines" == chunk.name() );

  CHECK_THAT( 2.1, WithinRel( chunk.energy() ) );
  CHECK( 33 == chunk.numberDiscreteCosines() );

  CHECK( 33 == chunk.cosines().size() );
  CHECK_THAT( -1., WithinRel( chunk.cosines().front() ) );
  CHECK_THAT( +1., WithinRel( chunk.cosines().back() ) );
}

DiscreteCosines makeDummyBlock() {

  return { 2, { -1.0, 1.0 } };
}
