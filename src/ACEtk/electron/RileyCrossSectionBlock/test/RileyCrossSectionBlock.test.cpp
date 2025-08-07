// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/RileyCrossSectionBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using RLY = electron::RLY;

std::vector< double > chunk();
void verifyBlock( const RLY&, const std::vector< double >& );
RLY makeDummyBlock();

SCENARIO( "RLY" ) {
  
  GIVEN( "valid data for a RileyCrossSectionBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      std::vector< std::vector< double > > rly_chunk;
      rly_chunk.resize( 9 );
      for ( unsigned int i = 0; i < 9; ++i ) {
        
        rly_chunk.at( i ).reserve( 14 );
        for ( unsigned int j = 0; j < 14; ++j )
          rly_chunk.at( i ).push_back( xss.at( 14 * i + j ) );
      }
      
      RLY block( rly_chunk[0], rly_chunk[1], rly_chunk[2],
                 rly_chunk[3], rly_chunk[4], rly_chunk[5],
                 rly_chunk[6], rly_chunk[7], rly_chunk[8] );
      
      THEN( "a RileyCrossSectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      RLY block( xss.begin(), xss.end() );
      
      THEN( "a RileyCrossSectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      RLY block( xss.begin(), xss.end() );
      RLY copy_block( block );
      
      THEN( "a RileyCrossSectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      RLY block( xss.begin(), xss.end() );
      RLY move_block( std::move( block ) );
      
      THEN( "a RileyCrossSectionBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      RLY block( xss.begin(), xss.end() );
      RLY copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a RileyCrossSectionBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      RLY block( xss.begin(), xss.end() );
      RLY move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a RileyCrossSectionBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  // from 26000.01e
  return { 256.0,               2.753945350000E-06,
           3.025708180000E+00,  8.903886980000E-01, 
          -2.412689590000E-04,  5.213269980000E-08,
          -4.608566620000E+00, -5.401426480000E+00, 
          -3.941929880000E+00, -2.344816820000E+00,
          -1.138809700000E+00, -4.129704450000E-01, 
          -8.415253760000E-02,  6.647649950000E-05,
           128.0,               9.442615900000E-06, 
          -1.791569670000E-01,  9.036438890000E-01,
          -5.827909060000E-04,  3.157744920000E-07, 
           1.408191320000E+00,  3.193788830000E+00,
           3.484815080000E+00,  2.821164200000E+00, 
           1.774414790000E+00,  8.069980240000E-01,
           1.979895820000E-01,  1.589867710000E-04, 
           64.0,                3.429432970000E-05,
           2.574029740000E+00,  8.053360130000E-01, 
          -9.566931430000E-04,  1.230600580000E-06,
          -3.350884910000E+00, -3.641381950000E+00, 
          -2.474028930000E+00, -1.376189250000E+00,
          -6.289431430000E-01, -2.177528000000E-01, 
          -4.480308190000E-02,  3.354566020000E-04,
           32.0,                1.298747450000E-04, 
           5.584700620000E+00,  5.487523300000E-01,
          -5.307862410000E-04,  2.724398750000E-07, 
          -7.604579960000E+00, -8.860380260000E+00,
          -6.384678240000E+00, -3.752287560000E+00, 
          -1.809440810000E+00, -6.591445330000E-01,
          -1.363195940000E-01,  2.800104540000E-04, 
           16.0,                5.045367270000E-04,
           6.589570900000E-01,  5.461468770000E-01, 
          -1.274174240000E-03,  1.647505770000E-06,
           1.155215050000E+00,  3.278234600000E+00, 
           3.817786710000E+00,  3.207764900000E+00,
           2.096348910000E+00,  1.009094120000E+00, 
           2.688509060000E-01,  6.396335770000E-04,
           8.0,                 1.987863320000E-03, 
           3.131311400000E+00,  3.166329930000E-01,
          -9.553143750000E-04,  1.781370050000E-06, 
          -3.288027500000E+00, -3.482316470000E+00,
          -2.412750460000E+00, -1.415701020000E+00, 
          -6.933956140000E-01, -2.591658090000E-01,
          -5.579142080000E-02,  9.759200810000E-04, 
           4.0,                 7.890526480000E-03,
           1.817617350000E+00,  2.014014110000E-01, 
          -9.727937130000E-04,  3.632412900000E-06,
          -1.327988320000E+00, -1.286864350000E+00, 
          -6.519743050000E-01, -1.877638260000E-01,
           1.908061670000E-02,  5.433346530000E-02, 
           2.261567870000E-02,  1.780581670000E-03,
           2.0,                 3.143989260000E-02, 
          -5.321295840000E-01,  1.891537440000E-01,
          -2.082484770000E-03,  1.664781540000E-05, 
           1.949275860000E+00,  2.490938990000E+00,
           2.401903800000E+00,  1.626504440000E+00, 
           9.089585130000E-01,  3.943779010000E-01,
           1.044917050000E-01,  3.720555090000E-03, 
           1.0,                 1.255147840000E-01,
          -1.062928400000E+00,  1.729343840000E-01, 
          -3.819201870000E-03,  5.596015950000E-05,
           2.049623930000E+00,  2.010232890000E+00, 
           1.862329940000E+00,  8.031157810000E-01,
           3.781372900000E-01,  1.369991900000E-01, 
           3.057833420000E-02,  7.223531600000E-03 };
}

void verifyBlock( const RLY& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "RLY" == block.name() );
  
  CHECK( 9 == block.NRLY() );
  CHECK( 9 == block.numberEnergyPoints() );
  CHECK( 14 == block.parameterSetLength() );
  
  CHECK_THAT( 256.0, WithinRel( block.energy( 1 ) ) );
  CHECK_THAT( 128.0, WithinRel( block.energy( 2 ) ) );
  CHECK_THAT( 64.0, WithinRel( block.energy( 3 ) ) );
  CHECK_THAT( 32.0, WithinRel( block.energy( 4 ) ) );
  CHECK_THAT( 16.0, WithinRel( block.energy( 5 ) ) );
  CHECK_THAT( 8.0, WithinRel( block.energy( 6 ) ) );
  CHECK_THAT( 4.0, WithinRel( block.energy( 7 ) ) );
  CHECK_THAT( 2.0, WithinRel( block.energy( 8 ) ) );
  CHECK_THAT( 1.0, WithinRel( block.energy( 9 ) ) );
  
  for ( unsigned int i = 0; i < block.NRLY(); ++i ) {
    
    unsigned int rly_index = i + 1;
    unsigned int xss_index_prefix = i * block.parameterSetLength();
    for ( unsigned int j = 0; j < block.parameterSetLength(); ++j ) {
      
      CHECK_THAT( xss[xss_index_prefix + j],
                  WithinRel( block.parameterSet( rly_index )[j] ) );
    }
  }
}

RLY makeDummyBlock() {
  
  return RLY(  );
}
