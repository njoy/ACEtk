// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/TabulatedKalbachMannDistribution.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using TabulatedKalbachMannDistribution = continuous::TabulatedKalbachMannDistribution;

std::vector< double > chunk();
void verifyChunk( const TabulatedKalbachMannDistribution&, const std::vector< double >& );
TabulatedKalbachMannDistribution makeDummyBlock();

SCENARIO( "TabulatedKalbachMannDistribution" ) {

  GIVEN( "valid data for a TabulatedKalbachMannDistribution instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      double incident = 2.1;
      int interpolation = 2;
      std::size_t discrete = 3;
      std::vector< double > cosines = { 1e-11, 1.0, 20.0 };
      std::vector< double > pdf = { 0.5, 0.5, 0.5 };
      std::vector< double > cdf = { 0.0, 0.5, 1.0 };
      std::vector< double > r = { 1., 2., 3. };
      std::vector< double > a = { 4., 5., 6. };

      TabulatedKalbachMannDistribution chunk( incident, interpolation,
                                              std::move( cosines ),
                                              std::move( pdf ),
                                              std::move( cdf ),
                                              std::move( r ),
                                              std::move( a ),
                                              discrete );

      THEN( "a TabulatedKalbachMannDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      double incident = 2.1;
      TabulatedKalbachMannDistribution chunk( incident, xss.begin(), xss.end() );

      THEN( "a TabulatedKalbachMannDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      TabulatedKalbachMannDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedKalbachMannDistribution copy( chunk );

      THEN( "an TabulatedKalbachMannDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      TabulatedKalbachMannDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedKalbachMannDistribution move( std::move( chunk ) );

      THEN( "an TabulatedKalbachMannDistribution can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      TabulatedKalbachMannDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedKalbachMannDistribution copy = makeDummyBlock();
      copy = chunk;

      THEN( "an TabulatedKalbachMannDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      TabulatedKalbachMannDistribution chunk( 2.1, xss.begin(), xss.end() );
      TabulatedKalbachMannDistribution move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an TabulatedKalbachMannDistribution can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return {                32,                  3,  1.00000000000E-11,  1.00000000000E+00,
           2.00000000000E+01,  0.50000000000E+00,  0.50000000000E+00,  0.50000000000E+00,
           0.00000000000E+00,  0.50000000000E+00,  1.00000000000E+00,  1.00000000000E+00,
           2.00000000000E+00,  3.00000000000E+00,  4.00000000000E+00,  5.00000000000E+00,
           6.00000000000E+00 };
}

void verifyChunk( const TabulatedKalbachMannDistribution& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 17 == chunk.length() );
  CHECK( "TabulatedKalbachMannDistribution" == chunk.name() );

  CHECK_THAT( 2.1, WithinRel( chunk.incidentEnergy() ) );
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

  CHECK( 3 == chunk.precompoundFractionValues().size() );
  CHECK_THAT( 1., WithinRel( chunk.precompoundFractionValues().front() ) );
  CHECK_THAT( 3., WithinRel( chunk.precompoundFractionValues().back() ) );

  CHECK( 3 == chunk.cdf().size() );
  CHECK_THAT( 4., WithinRel( chunk.angularDistributionSlopeValues().front() ) );
  CHECK_THAT( 6., WithinRel( chunk.angularDistributionSlopeValues().back() ) );
}

TabulatedKalbachMannDistribution makeDummyBlock() {

  return { 1., 1, { 1., 2. }, { 3., 4. }, { 5., 6. }, { 7., 8. }, { 9., 10. }, 1 };
}
