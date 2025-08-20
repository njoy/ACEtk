// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/BremsstrahlungHighFrequencyBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using HFB = electron::HFB;

std::vector< double > chunk();
void verifyBlock( const HFB&, const std::vector< double >& );
HFB makeDummyBlock();

SCENARIO( "HFB" ) {
  
  GIVEN( "valid data for a BremsstrahlungHighFrequencyBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      HFB block( { xss[0], xss[1], xss[2] }, { xss[3], xss[4], xss[5] } );
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      HFB block( xss.begin(), xss.end(), 3 );
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      HFB block( xss.begin(), xss.end(), 3 );
      HFB copy_block( block );
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      HFB block( xss.begin(), xss.end(), 3 );
      HFB move_block( std::move( block ) );
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      HFB block( xss.begin(), xss.end(), 3 );
      HFB copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      HFB block( xss.begin(), xss.end(), 3 );
      HFB move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a BremsstrahlungHighFrequencyBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  return { 0.1, 1.0, 10.0, 0.2, 1.2, 3.0 };
}

void verifyBlock( const HFB& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "HFB" == block.name() );
  
  CHECK( 3 == block.NHFB() );
  CHECK( 3 == block.numberEnergyPoints() );
  
  CHECK_THAT( xss[0], WithinRel( block.energies()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.energies()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.energies()[2] ) );
  
  CHECK_THAT( xss[3], WithinRel( block.crossSections()[0] ) );
  CHECK_THAT( xss[4], WithinRel( block.crossSections()[1] ) );
  CHECK_THAT( xss[5], WithinRel( block.crossSections()[2] ) );
}

HFB makeDummyBlock() {
  
  return HFB( { 1.0, 2.0 }, { 3.0, 4.0 } );
}
