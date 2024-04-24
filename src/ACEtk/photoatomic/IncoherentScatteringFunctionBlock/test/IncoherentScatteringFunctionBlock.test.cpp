// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using IncoherentScatteringFunctionBlock = photoatomic::IncoherentScatteringFunctionBlock;

std::vector< double > chunk();
std::vector< double > chunkEprdata();
void verifyChunk( const IncoherentScatteringFunctionBlock& );
void verifyChunkEprdata( const IncoherentScatteringFunctionBlock& );

SCENARIO( "IncoherentScatteringFunctionBlock" ) {

  GIVEN( "valid data for a IncoherentScatteringFunctionBlock instance - mcplib style" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > values = {

                                                                                         0,
         1.104680000000E-03,  4.409660000000E-03,  1.033110000000E-01,  3.425650000000E-01,
         5.887310000000E-01,  7.688390000000E-01,  9.368610000000E-01,  9.829840000000E-01,
         9.950160000000E-01,  9.983740000000E-01,  9.994100000000E-01,  9.997650000000E-01,
         9.998980000000E-01,  9.999530000000E-01,  9.999980000000E-01,                   1,
                          1,                   1,                   1,                   1
       };

      IncoherentScatteringFunctionBlock chunk( std::move( values ) );

      THEN( "a IncoherentScatteringFunctionBlock can be constructed and members can "
            "be tested" ) {

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

      IncoherentScatteringFunctionBlock chunk( xss.begin(), xss.end() );

      THEN( "a IncoherentScatteringFunctionBlock can be constructed and members can "
            "be tested" ) {

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

  GIVEN( "valid data for a IncoherentScatteringFunctionBlock instance - eprdata style" ) {

    std::vector< double > xss = chunkEprdata();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > momentum = { 0., 1., 1000., 1e+6, 1e+9 };
      std::vector< double > values = { 1., 2., 3., 4., 5. };

      IncoherentScatteringFunctionBlock chunk( std::move( momentum ),
                                               std::move( values ) );

      THEN( "a IncoherentScatteringFunctionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkEprdata( chunk );
      } // THEN

      THEN( "the XSS array is correct" ) {

        auto xss_chunk = chunk.XSS();
        for ( unsigned int i = 0; i < chunk.length(); ++i ) {

          CHECK_THAT( xss[i], WithinRel( xss_chunk[i] ) );
        }
      } // THEN
    } // WHEN

    WHEN( "the data is defined by iterators" ) {

      IncoherentScatteringFunctionBlock chunk( xss.begin(), xss.end() );

      THEN( "a IncoherentScatteringFunctionBlock can be constructed and members can "
            "be tested" ) {

        verifyChunkEprdata( chunk );
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
                                                                                           0,
           1.104680000000E-03,  4.409660000000E-03,  1.033110000000E-01,  3.425650000000E-01,
           5.887310000000E-01,  7.688390000000E-01,  9.368610000000E-01,  9.829840000000E-01,
           9.950160000000E-01,  9.983740000000E-01,  9.994100000000E-01,  9.997650000000E-01,
           9.998980000000E-01,  9.999530000000E-01,  9.999980000000E-01,                   1,
                            1,                   1,                   1,                   1
  };
}

std::vector< double > chunkEprdata() {

  return {

    0., 1., 1000., 1e+6, 1e+9,
    1., 2., 3., 4., 5.
  };
}

void verifyChunk( const IncoherentScatteringFunctionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 21 == chunk.length() );
  CHECK( "JINC" == chunk.name() );

  CHECK( 21 == chunk.NM() );
  CHECK( 21 == chunk.numberValues() );

  CHECK( 21 == chunk.momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.momentum()[0] ) );
  CHECK_THAT( .005, WithinRel( chunk.momentum()[1] ) );
  CHECK_THAT( .01 , WithinRel( chunk.momentum()[2] ) );
  CHECK_THAT( .05 , WithinRel( chunk.momentum()[3] ) );
  CHECK_THAT( .1  , WithinRel( chunk.momentum()[4] ) );
  CHECK_THAT( .15 , WithinRel( chunk.momentum()[5] ) );
  CHECK_THAT( .2  , WithinRel( chunk.momentum()[6] ) );
  CHECK_THAT( .3  , WithinRel( chunk.momentum()[7] ) );
  CHECK_THAT( .4  , WithinRel( chunk.momentum()[8] ) );
  CHECK_THAT( .5  , WithinRel( chunk.momentum()[9] ) );
  CHECK_THAT( .6  , WithinRel( chunk.momentum()[10] ) );
  CHECK_THAT( .7  , WithinRel( chunk.momentum()[11] ) );
  CHECK_THAT( .8  , WithinRel( chunk.momentum()[12] ) );
  CHECK_THAT( .9  , WithinRel( chunk.momentum()[13] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.momentum()[14] ) );
  CHECK_THAT( 1.5 , WithinRel( chunk.momentum()[15] ) );
  CHECK_THAT( 2.  , WithinRel( chunk.momentum()[16] ) );
  CHECK_THAT( 3.  , WithinRel( chunk.momentum()[17] ) );
  CHECK_THAT( 4.  , WithinRel( chunk.momentum()[18] ) );
  CHECK_THAT( 5.  , WithinRel( chunk.momentum()[19] ) );
  CHECK_THAT( 8.  , WithinRel( chunk.momentum()[20] ) );

  CHECK( 21 == chunk.values().size() );
  CHECK_THAT( 0, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 1.104680000000E-03, WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 4.409660000000E-03, WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 1.033110000000E-01, WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 3.425650000000E-01, WithinRel( chunk.values()[4] ) );
  CHECK_THAT( 5.887310000000E-01, WithinRel( chunk.values()[5] ) );
  CHECK_THAT( 7.688390000000E-01, WithinRel( chunk.values()[6] ) );
  CHECK_THAT( 9.368610000000E-01, WithinRel( chunk.values()[7] ) );
  CHECK_THAT( 9.829840000000E-01, WithinRel( chunk.values()[8] ) );
  CHECK_THAT( 9.950160000000E-01, WithinRel( chunk.values()[9] ) );
  CHECK_THAT( 9.983740000000E-01, WithinRel( chunk.values()[10] ) );
  CHECK_THAT( 9.994100000000E-01, WithinRel( chunk.values()[11] ) );
  CHECK_THAT( 9.997650000000E-01, WithinRel( chunk.values()[12] ) );
  CHECK_THAT( 9.998980000000E-01, WithinRel( chunk.values()[13] ) );
  CHECK_THAT( 9.999530000000E-01, WithinRel( chunk.values()[14] ) );
  CHECK_THAT( 9.999980000000E-01, WithinRel( chunk.values()[15] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[16] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[17] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[18] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[19] ) );
  CHECK_THAT( 1, WithinRel( chunk.values()[20] ) );
}

void verifyChunkEprdata( const IncoherentScatteringFunctionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 10 == chunk.length() );
  CHECK( "JINC" == chunk.name() );

  CHECK( 5 == chunk.NM() );
  CHECK( 5 == chunk.numberValues() );

  CHECK( 5 == chunk.momentum().size() );
  CHECK_THAT( 0.  , WithinRel( chunk.momentum()[0] ) );
  CHECK_THAT( 1.  , WithinRel( chunk.momentum()[1] ) );
  CHECK_THAT( 1e+3, WithinRel( chunk.momentum()[2] ) );
  CHECK_THAT( 1e+6, WithinRel( chunk.momentum()[3] ) );
  CHECK_THAT( 1e+9, WithinRel( chunk.momentum()[4] ) );

  CHECK( 5 == chunk.values().size() );
  CHECK_THAT( 1, WithinRel( chunk.values()[0] ) );
  CHECK_THAT( 2., WithinRel( chunk.values()[1] ) );
  CHECK_THAT( 3., WithinRel( chunk.values()[2] ) );
  CHECK_THAT( 4., WithinRel( chunk.values()[3] ) );
  CHECK_THAT( 5., WithinRel( chunk.values()[4] ) );
}
