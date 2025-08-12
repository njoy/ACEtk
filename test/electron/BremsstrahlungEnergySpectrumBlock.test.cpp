// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/BremsstrahlungEnergySpectrumBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using RKT = electron::RKT;

std::vector< double > chunk();
void verifyBlock( const RKT&, const std::vector< double >& );
RKT makeDummyBlock();

SCENARIO( "RKT" ) {
  
  GIVEN( "valid data for a BremsstrahlungEnergySpectrumBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      RKT block( xss );
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      RKT block( xss.begin(), xss.end(), 5 );
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      RKT block( xss.begin(), xss.end(), 5 );
      RKT copy_block( block );
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      RKT block( xss.begin(), xss.end(), 5 );
      RKT move_block( std::move( block ) );
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      RKT block( xss.begin(), xss.end(), 5 );
      RKT copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      RKT block( xss.begin(), xss.end(), 5 );
      RKT move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a BremsstrahlungEnergySpectrumBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  return { 0.001, 0.25, 0.50, 0.80, 0.9999 };
}

void verifyBlock( const RKT& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "RKT" == block.name() );
  
  CHECK( 5 == block.NRKT() );
  CHECK( 5 == block.numberPhotonEnergyRatios() );
  
  CHECK_THAT( xss[0], WithinRel( block.photonEnergyRatios()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.photonEnergyRatios()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.photonEnergyRatios()[2] ) );
  CHECK_THAT( xss[3], WithinRel( block.photonEnergyRatios()[3] ) );
  CHECK_THAT( xss[4], WithinRel( block.photonEnergyRatios()[4] ) );
}

RKT makeDummyBlock() {
  
  return RKT( { 1.0, 2.0 } );
}
