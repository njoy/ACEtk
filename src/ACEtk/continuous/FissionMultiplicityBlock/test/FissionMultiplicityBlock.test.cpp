#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/continuous/FissionMultiplicityBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using FissionMultiplicityBlock = block::FissionMultiplicityBlock;
using PolynomialFissionMultiplicity = block::PolynomialFissionMultiplicity;
using TabulatedFissionMultiplicity = block::TabulatedFissionMultiplicity;

std::vector< double > chunk();
std::vector< double > chunkWithPromptAndTotal();
void verifyChunk( const FissionMultiplicityBlock& );
void verifyChunkWithPromptAndTotal( const FissionMultiplicityBlock& );

SCENARIO( "FissionMultiplicityBlock" ) {

  GIVEN( "valid data for an FissionMultiplicityBlock instance using prompt nu only" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      TabulatedFissionMultiplicity prompt( { 1e-11, 1., 20. }, { 2.5, 2.65, 3.5 } );

      FissionMultiplicityBlock chunk( std::move( prompt ) );

      THEN( "an FissionMultiplicityBlock can be constructed and members can be tested" ) {

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

      FissionMultiplicityBlock chunk( xss.begin(), xss.end() );

      THEN( "an FissionMultiplicityBlock can be constructed and members can be tested" ) {

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

  GIVEN( "valid data for an FissionMultiplicityBlock instance using both "
         "prompt and total nu" ) {

    std::vector< double > xss = chunkWithPromptAndTotal();

    WHEN( "the data is given explicitly" ) {

      TabulatedFissionMultiplicity prompt( { 1e-11, 1., 20. }, { 2.5, 2.65, 3.5 } );
      PolynomialFissionMultiplicity total( { 2.35, 1e-3 } );

      FissionMultiplicityBlock chunk( std::move( prompt ), std::move( total ) );

      THEN( "an FissionMultiplicityBlock can be constructed and members can be tested" ) {

        verifyChunkWithPromptAndTotal( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      FissionMultiplicityBlock chunk( xss.begin(), xss.end() );

      THEN( "an FissionMultiplicityBlock can be constructed and members can be tested" ) {

        verifyChunkWithPromptAndTotal( chunk );
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

  return { 2, 0, 3, 1e-11, 1., 20., 2.5, 2.65, 3.5 };
}

std::vector< double > chunkWithPromptAndTotal() {

  return { -9, 2, 0, 3, 1e-11, 1., 20., 2.5, 2.65, 3.5,
               1, 2, 2.35, 1e-3 };
}

void verifyChunk( const FissionMultiplicityBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 9 == chunk.length() );
  CHECK( "NU" == chunk.name() );

  CHECK( false == chunk.hasPromptAndTotalFissionMultiplicity() );

  auto multiplicity = std::get< TabulatedFissionMultiplicity >( chunk.multiplicity() );
  CHECK( 2 == multiplicity.LNU() );
  CHECK( 2 == multiplicity.type() );

  CHECK( 0 == multiplicity.interpolationData().NB() );
  CHECK( 0 == multiplicity.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == multiplicity.interpolationData().INT().size() );
  CHECK( 0 == multiplicity.interpolationData().interpolants().size() );
  CHECK( 0 == multiplicity.interpolationData().NBT().size() );
  CHECK( 0 == multiplicity.interpolationData().boundaries().size() );

  CHECK( 0 == multiplicity.NB() );
  CHECK( 0 == multiplicity.numberInterpolationRegions() );
  CHECK( 0 == multiplicity.INT().size() );
  CHECK( 0 == multiplicity.interpolants().size() );
  CHECK( 0 == multiplicity.NBT().size() );
  CHECK( 0 == multiplicity.boundaries().size() );

  CHECK( 3 == multiplicity.NE() );
  CHECK( 3 == multiplicity.numberValues() );

  CHECK( 3 == multiplicity.energies().size() );
  CHECK( 1e-11 == Approx( multiplicity.energies()[0] ) );
  CHECK( 1. == Approx( multiplicity.energies()[1] ) );
  CHECK( 20. == Approx( multiplicity.energies()[2] ) );

  CHECK( 3 == multiplicity.multiplicities().size() );
  CHECK( 2.5 == Approx( multiplicity.multiplicities()[0] ) );
  CHECK( 2.65 == Approx( multiplicity.multiplicities()[1] ) );
  CHECK( 3.5 == Approx( multiplicity.multiplicities()[2] ) );

  CHECK( std::nullopt == chunk.totalFissionMultiplicity() );
}

void verifyChunkWithPromptAndTotal( const FissionMultiplicityBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 14 == chunk.length() );
  CHECK( "NU" == chunk.name() );

  CHECK( true == chunk.hasPromptAndTotalFissionMultiplicity() );

  auto multiplicity = std::get< TabulatedFissionMultiplicity >( chunk.multiplicity() );
  CHECK( 2 == multiplicity.LNU() );
  CHECK( 2 == multiplicity.type() );

  CHECK( 0 == multiplicity.interpolationData().NB() );
  CHECK( 0 == multiplicity.interpolationData().numberInterpolationRegions() );
  CHECK( 0 == multiplicity.interpolationData().INT().size() );
  CHECK( 0 == multiplicity.interpolationData().interpolants().size() );
  CHECK( 0 == multiplicity.interpolationData().NBT().size() );
  CHECK( 0 == multiplicity.interpolationData().boundaries().size() );

  CHECK( 0 == multiplicity.NB() );
  CHECK( 0 == multiplicity.numberInterpolationRegions() );
  CHECK( 0 == multiplicity.INT().size() );
  CHECK( 0 == multiplicity.interpolants().size() );
  CHECK( 0 == multiplicity.NBT().size() );
  CHECK( 0 == multiplicity.boundaries().size() );

  CHECK( 3 == multiplicity.NE() );
  CHECK( 3 == multiplicity.numberValues() );

  CHECK( 3 == multiplicity.energies().size() );
  CHECK( 1e-11 == Approx( multiplicity.energies()[0] ) );
  CHECK( 1. == Approx( multiplicity.energies()[1] ) );
  CHECK( 20. == Approx( multiplicity.energies()[2] ) );

  CHECK( 3 == multiplicity.multiplicities().size() );
  CHECK( 2.5 == Approx( multiplicity.multiplicities()[0] ) );
  CHECK( 2.65 == Approx( multiplicity.multiplicities()[1] ) );
  CHECK( 3.5 == Approx( multiplicity.multiplicities()[2] ) );

  auto total = std::get< PolynomialFissionMultiplicity >( chunk.totalFissionMultiplicity().value() );
  CHECK( 1 == total.LNU() );
  CHECK( 1 == total.type() );

  CHECK( 2 == total.NC() );
  CHECK( 2 == total.numberCoefficients() );

  CHECK( 2 == total.coefficients().size() );
  CHECK( 2.35 == Approx( total.coefficients()[0] ) );
  CHECK( 1e-3 == Approx( total.coefficients()[1] ) );
}
