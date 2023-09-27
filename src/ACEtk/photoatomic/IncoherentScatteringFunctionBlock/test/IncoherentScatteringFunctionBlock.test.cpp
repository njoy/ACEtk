#define CATCH_CONFIG_MAIN

#include "catch.hpp"
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

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
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

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
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

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
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

          CHECK( xss[i] == Approx( xss_chunk[i] ) );
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
  CHECK( 0.   == Approx( chunk.momentum()[0] ) );
  CHECK( .005 == Approx( chunk.momentum()[1] ) );
  CHECK( .01  == Approx( chunk.momentum()[2] ) );
  CHECK( .05  == Approx( chunk.momentum()[3] ) );
  CHECK( .1   == Approx( chunk.momentum()[4] ) );
  CHECK( .15  == Approx( chunk.momentum()[5] ) );
  CHECK( .2   == Approx( chunk.momentum()[6] ) );
  CHECK( .3   == Approx( chunk.momentum()[7] ) );
  CHECK( .4   == Approx( chunk.momentum()[8] ) );
  CHECK( .5   == Approx( chunk.momentum()[9] ) );
  CHECK( .6   == Approx( chunk.momentum()[10] ) );
  CHECK( .7   == Approx( chunk.momentum()[11] ) );
  CHECK( .8   == Approx( chunk.momentum()[12] ) );
  CHECK( .9   == Approx( chunk.momentum()[13] ) );
  CHECK( 1.   == Approx( chunk.momentum()[14] ) );
  CHECK( 1.5  == Approx( chunk.momentum()[15] ) );
  CHECK( 2.   == Approx( chunk.momentum()[16] ) );
  CHECK( 3.   == Approx( chunk.momentum()[17] ) );
  CHECK( 4.   == Approx( chunk.momentum()[18] ) );
  CHECK( 5.   == Approx( chunk.momentum()[19] ) );
  CHECK( 8.   == Approx( chunk.momentum()[20] ) );

  CHECK( 21 == chunk.values().size() );
  CHECK( 0 == Approx( chunk.values()[0] ) );
  CHECK( 1.104680000000E-03 == Approx( chunk.values()[1] ) );
  CHECK( 4.409660000000E-03 == Approx( chunk.values()[2] ) );
  CHECK( 1.033110000000E-01 == Approx( chunk.values()[3] ) );
  CHECK( 3.425650000000E-01 == Approx( chunk.values()[4] ) );
  CHECK( 5.887310000000E-01 == Approx( chunk.values()[5] ) );
  CHECK( 7.688390000000E-01 == Approx( chunk.values()[6] ) );
  CHECK( 9.368610000000E-01 == Approx( chunk.values()[7] ) );
  CHECK( 9.829840000000E-01 == Approx( chunk.values()[8] ) );
  CHECK( 9.950160000000E-01 == Approx( chunk.values()[9] ) );
  CHECK( 9.983740000000E-01 == Approx( chunk.values()[10] ) );
  CHECK( 9.994100000000E-01 == Approx( chunk.values()[11] ) );
  CHECK( 9.997650000000E-01 == Approx( chunk.values()[12] ) );
  CHECK( 9.998980000000E-01 == Approx( chunk.values()[13] ) );
  CHECK( 9.999530000000E-01 == Approx( chunk.values()[14] ) );
  CHECK( 9.999980000000E-01 == Approx( chunk.values()[15] ) );
  CHECK( 1 == Approx( chunk.values()[16] ) );
  CHECK( 1 == Approx( chunk.values()[17] ) );
  CHECK( 1 == Approx( chunk.values()[18] ) );
  CHECK( 1 == Approx( chunk.values()[19] ) );
  CHECK( 1 == Approx( chunk.values()[20] ) );
}

void verifyChunkEprdata( const IncoherentScatteringFunctionBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 10 == chunk.length() );
  CHECK( "JINC" == chunk.name() );

  CHECK( 5 == chunk.NM() );
  CHECK( 5 == chunk.numberValues() );

  CHECK( 5 == chunk.momentum().size() );
  CHECK( 0.   == Approx( chunk.momentum()[0] ) );
  CHECK( 1.   == Approx( chunk.momentum()[1] ) );
  CHECK( 1e+3 == Approx( chunk.momentum()[2] ) );
  CHECK( 1e+6 == Approx( chunk.momentum()[3] ) );
  CHECK( 1e+9 == Approx( chunk.momentum()[4] ) );

  CHECK( 5 == chunk.values().size() );
  CHECK( 1 == Approx( chunk.values()[0] ) );
  CHECK( 2. == Approx( chunk.values()[1] ) );
  CHECK( 3. == Approx( chunk.values()[2] ) );
  CHECK( 4. == Approx( chunk.values()[3] ) );
  CHECK( 5. == Approx( chunk.values()[4] ) );
}
