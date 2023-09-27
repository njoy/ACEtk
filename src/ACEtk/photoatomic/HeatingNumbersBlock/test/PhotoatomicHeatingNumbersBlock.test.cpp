#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using PhotoatomicHeatingNumbersBlock = block::PhotoatomicHeatingNumbersBlock;

std::vector< double > chunk();
void verifyChunk( const PhotoatomicHeatingNumbersBlock& );

SCENARIO( "PhotoatomicHeatingNumbersBlock" ) {

  GIVEN( "valid data for a PhotoatomicHeatingNumbersBlock instance" ) {

    std::vector< double > xss = chunk();

    WHEN( "the data is given explicitly" ) {

      std::vector< double > heating = {

                                                  9.457315870945E-04,  1.225405765983E-03,
        1.256045266042E-03,  9.011338843679E-04,  5.697552004817E-04,  3.847584963574E-04,
        2.911895331229E-04,  2.335442942103E-04,  2.531421561301E-04,  4.380333557943E-04,
        7.330696630483E-04,  1.565659741856E-03,  2.677466560596E-03,  4.036623399525E-03,
        5.618462697630E-03,  9.370364810281E-03,  1.379990752209E-02,  2.723188049578E-02,
        4.326571133116E-02,  8.088732501359E-02,  1.238397003592E-01,  1.706716486304E-01,
        2.204973168250E-01,  3.269163222828E-01,  4.400308708052E-01,  4.527965097968E-01,
        7.419466764524E-01,  1.061565528270E+00,  1.090315311278E+00,  1.733132238815E+00,
        2.433371347510E+00,  3.154191701719E+00,  3.890326612973E+00,  5.403447105576E+00,
        6.966207437556E+00,  1.100530360055E+01,  1.522741150508E+01,  2.401044125224E+01,
        3.311428069815E+01,  4.246770168873E+01,  5.194711053011E+01,  7.125317441480E+01,
        9.086036433693E+01
      };

      PhotoatomicHeatingNumbersBlock chunk( std::move( heating ) );

      THEN( "a PhotoatomicHeatingNumbersBlock can be constructed and members can "
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

      PhotoatomicHeatingNumbersBlock chunk( xss.begin(), xss.end(), 43 );

      THEN( "a PhotoatomicHeatingNumbersBlock can be constructed and members can "
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
} // SCENARIO

std::vector< double > chunk() {

  return {

                                              9.457315870945E-04,  1.225405765983E-03,
    1.256045266042E-03,  9.011338843679E-04,  5.697552004817E-04,  3.847584963574E-04,
    2.911895331229E-04,  2.335442942103E-04,  2.531421561301E-04,  4.380333557943E-04,
    7.330696630483E-04,  1.565659741856E-03,  2.677466560596E-03,  4.036623399525E-03,
    5.618462697630E-03,  9.370364810281E-03,  1.379990752209E-02,  2.723188049578E-02,
    4.326571133116E-02,  8.088732501359E-02,  1.238397003592E-01,  1.706716486304E-01,
    2.204973168250E-01,  3.269163222828E-01,  4.400308708052E-01,  4.527965097968E-01,
    7.419466764524E-01,  1.061565528270E+00,  1.090315311278E+00,  1.733132238815E+00,
    2.433371347510E+00,  3.154191701719E+00,  3.890326612973E+00,  5.403447105576E+00,
    6.966207437556E+00,  1.100530360055E+01,  1.522741150508E+01,  2.401044125224E+01,
    3.311428069815E+01,  4.246770168873E+01,  5.194711053011E+01,  7.125317441480E+01,
    9.086036433693E+01
  };
}

void verifyChunk( const PhotoatomicHeatingNumbersBlock& chunk ) {

  CHECK( false == chunk.empty() );
  CHECK( 43 == chunk.length() );
  CHECK( "LHNM" == chunk.name() );

  CHECK( 43 == chunk.XSS().size() );

  CHECK( 43 == chunk.NES() );
  CHECK( 43 == chunk.numberEnergyPoints() );
  CHECK( 43 == chunk.heating().size() );

  CHECK( 9.457315870945E-04 == Approx( chunk.heating().front() ) );
  CHECK( 9.086036433693E+01 == Approx( chunk.heating().back() ) );
}
