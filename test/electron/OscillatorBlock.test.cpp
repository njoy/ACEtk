// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/OscillatorBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using OSC = electron::OSC;

std::vector< double > chunk();
void verifyBlock( const OSC&, const std::vector< double >& );
OSC makeDummyBlock();

SCENARIO( "OSC" ) {
  
  GIVEN( "valid data for a OscillatorBlock instance" ) {
    
    std::vector< double > xss = chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      OSC block( { xss[0], xss[1], xss[2] }, { xss[3], xss[4], xss[5] } );
      
      THEN( "a OscillatorBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      OSC block( xss.begin(), xss.end(), 3 );
      
      THEN( "a OscillatorBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      OSC block( xss.begin(), xss.end(), 3 );
      OSC copy_block( block );
      
      THEN( "a OscillatorBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      OSC block( xss.begin(), xss.end(), 3 );
      OSC move_block( std::move( block ) );
      
      THEN( "a OscillatorBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      OSC block( xss.begin(), xss.end(), 3 );
      OSC copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a OscillatorBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      OSC block( xss.begin(), xss.end(), 3 );
      OSC move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a OscillatorBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > chunk() {
  
  // adapted from 6000.03e
  return { 2.0, 2.0, -2.0, 288.0, 16.59, 11.26 };
}

void verifyBlock( const OSC& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "OSC" == block.name() );
  
  CHECK( 3 == block.NOSC() );
  CHECK( 3 == block.numberOscillators() );
  
  CHECK_THAT( xss[0], WithinRel( block.occupationNumbers()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.occupationNumbers()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.occupationNumbers()[2] ) );
  
  CHECK_THAT( xss[3], WithinRel( block.bindingEnergies()[0] ) );
  CHECK_THAT( xss[4], WithinRel( block.bindingEnergies()[1] ) );
  CHECK_THAT( xss[5], WithinRel( block.bindingEnergies()[2] ) );
}

OSC makeDummyBlock() {
  
  return OSC( { 1.0, 2.0 }, { 3.0, 4.0 } );
}
