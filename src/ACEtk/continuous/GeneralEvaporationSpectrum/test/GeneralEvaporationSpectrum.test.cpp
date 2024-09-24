// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/continuous/GeneralEvaporationSpectrum.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using GeneralEvaporationSpectrum = continuous::GeneralEvaporationSpectrum;

std::vector< double > chunk();
void verifyChunk( const GeneralEvaporationSpectrum&, const std::vector< double >& );
GeneralEvaporationSpectrum makeDummyBlock();

SCENARIO( "GeneralEvaporationSpectrum" ) {

  GIVEN( "valid data for a GeneralEvaporationSpectrum instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > energies = { 1e-5, 1., 10., 20. };
      std::vector< double > temperatures = { 1., 2., 3., 4. };
      std::vector< double > bins = { 5., 6., 7. };

      GeneralEvaporationSpectrum chunk( std::move( energies ),
                                        std::move( temperatures ),
                                        std::move( bins ) );

      THEN( "a GeneralEvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      GeneralEvaporationSpectrum chunk( xss.begin(), xss.end() );

      THEN( "a GeneralEvaporationSpectrum can be constructed and members can be tested" ) {

        verifyChunk( chunk, xss );
      } // THEN
    } // WHEN

    WHEN( "using the copy constructor" ) {

      GeneralEvaporationSpectrum chunk( xss.begin(), xss.end() );
      GeneralEvaporationSpectrum copy( chunk );

      THEN( "an GeneralEvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using the move constructor" ) {

      GeneralEvaporationSpectrum chunk( xss.begin(), xss.end() );
      GeneralEvaporationSpectrum move( std::move( chunk ) );

      THEN( "an GeneralEvaporationSpectrum can be constructed and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN

    WHEN( "using copy assignment" ) {

      GeneralEvaporationSpectrum chunk( xss.begin(), xss.end() );
      GeneralEvaporationSpectrum copy = makeDummyBlock();
      copy = chunk;

      THEN( "an GeneralEvaporationSpectrum can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( copy, xss );
      } // THEN
    } // WHEN

    WHEN( "using move assignment" ) {

      GeneralEvaporationSpectrum chunk( xss.begin(), xss.end() );
      GeneralEvaporationSpectrum move = makeDummyBlock();
      move = std::move( chunk );

      THEN( "an GeneralEvaporationSpectrum can be copy assigned and "
            "members can be tested" ) {

        verifyChunk( move, xss );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::vector< double > chunk() {

  return { 0,
           4, 1e-5, 1., 10., 20., 1., 2., 3., 4.,
           3, 5., 6., 7. };
}

void verifyChunk( const GeneralEvaporationSpectrum& chunk,
                  const std::vector< double >& xss ) {

  // XSS

  auto xss_chunk = chunk.XSS();
  for ( unsigned int i = 0; i < chunk.length(); ++i ) {

    CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
  }

  // interface

  CHECK( false == chunk.empty() );
  CHECK( 14 == chunk.length() );
  CHECK( "GeneralEvaporationSpectrum" == chunk.name() );

  CHECK( EnergyDistributionType::GeneralEvaporation == chunk.LAW() );
  CHECK( EnergyDistributionType::GeneralEvaporation == chunk.type() );

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

  CHECK( 4 == chunk.NE() );
  CHECK( 4 == chunk.numberEnergyPoints() );

  CHECK( 4 == chunk.energies().size() );
  CHECK_THAT( 1e-05, WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 10., WithinRel( chunk.energies()[2] ) );
  CHECK_THAT( 20., WithinRel( chunk.energies()[3] ) );

  CHECK( 4 == chunk.temperatures().size() );
  CHECK_THAT( 1., WithinRel( chunk.temperatures()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.temperatures()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.temperatures()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.temperatures()[3] ) );

  CHECK_THAT( 1e-5, WithinRel( chunk.minimumIncidentEnergy() ) );
  CHECK_THAT( 20., WithinRel( chunk.maximumIncidentEnergy() ) );

  CHECK( 3 == chunk.NET() );
  CHECK( 2 == chunk.numberBins() );

  CHECK( 3 == chunk.bins().size() );
  CHECK_THAT( 5., WithinRel( chunk.bins()[0] ) );
  CHECK_THAT( 6., WithinRel( chunk.bins()[1] ) );
  CHECK_THAT( 7., WithinRel( chunk.bins()[2] ) );
}

GeneralEvaporationSpectrum makeDummyBlock() {

  return { { 1., 2. }, { 3., 4. }, { 5., 6. } };
}
