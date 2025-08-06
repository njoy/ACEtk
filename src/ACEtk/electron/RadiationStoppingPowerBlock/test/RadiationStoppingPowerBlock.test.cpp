// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/electron/RadiationStoppingPowerBlock.hpp"

// other includes

// convenience typedefs
using namespace njoy::ACEtk;
using RAD = electron::RAD;

std::vector< double > el_chunk();
std::vector< double > el03_chunk();
void verifyBlock( const RAD&, const std::vector< double >& );
RAD makeDummyBlock();

SCENARIO( "RadiationStoppingPowerBlock" ) {
  
  GIVEN( "valid data for a EL format RadiationStoppingPowerBlock instance" ) {
    
    std::vector< double > xss = el_chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      std::vector< double > energies = { xss[0], xss[1], xss[2] };
      std::vector< double > stoppingpowers = { xss[3], xss[4], xss[5] };
      RAD block( energies, stoppingpowers );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      RAD block( xss.begin(), xss.end(), 3, 0 );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 0 );
      RAD copy_block( block );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 0 );
      RAD move_block( std::move( block ) );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 0 );
      RAD copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a RadiationStoppingPowerBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 0 );
      RAD move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a RadiationStoppingPowerBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
  
  GIVEN( "valid data for a EL03 format RadiationStoppingPowerBlock instance" ) {
    
    std::vector< double > xss = el03_chunk();
    
    WHEN( "the data is given explicitly" ) {
      
      std::vector< double > energies = { xss[0], xss[1], xss[2] };
      std::vector< double > stoppingpowers = { xss[3], xss[4], xss[5] };
      std::vector< double > corrections = { xss[6], xss[7], xss[8] };
      RAD block( energies, stoppingpowers, corrections );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "the data is defined by iterators"  ) {
      
      RAD block( xss.begin(), xss.end(), 3, 3 );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the copy constructor" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 3 );
      RAD copy_block( block );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using the move constructor" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 3 );
      RAD move_block( std::move( block ) );
      
      THEN( "a RadiationStoppingPowerBlock can be constructed "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using copy assignment" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 3 );
      RAD copy_block = makeDummyBlock();
      copy_block = block;
      
      THEN( "a RadiationStoppingPowerBlock can be copy assigned "
            "and members can be tested" ) {
        
        verifyBlock( copy_block, xss );
      }  // THEN
    }  // WHEN
    
    WHEN ( "using move assignment" ) {
      
      RAD block( xss.begin(), xss.end(), 3, 3 );
      RAD move_block = makeDummyBlock();
      move_block = std::move( block );
      
      THEN( "a RadiationStoppingPowerBlock can be move assigned "
            "and members can be tested" ) {
        
        verifyBlock( move_block, xss );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

std::vector< double > el_chunk() {
  
  return { 0.1, 1.0, 10.0, 0.2, 1.2, 3.0 };
}

std::vector< double > el03_chunk() {
  
  return { 0.1, 1.0, 10.0, 0.2, 1.2, 3.0, 1.05, 1.15, 1.02 };
}

void verifyBlock( const RAD& block, const std::vector< double >& xss ) {
  
  // verify xss
  auto xss_block = block.XSS();
  for ( unsigned int i = 0; i < block.length(); ++i ) {
    
    CHECK_THAT( xss[i], WithinRel( xss_block[i] ) );
  }
  
  // verify block interface
  CHECK( false == block.empty() );
  CHECK( xss.size() == block.length() );
  CHECK( "RAD" == block.name() );
  
  CHECK( 3 == block.NRAD() );
  CHECK( 3 == block.numberEnergyPoints() );
  
  CHECK_THAT( xss[0], WithinRel( block.energies()[0] ) );
  CHECK_THAT( xss[1], WithinRel( block.energies()[1] ) );
  CHECK_THAT( xss[2], WithinRel( block.energies()[2] ) );
  
  CHECK_THAT( xss[3], WithinRel( block.stoppingPowers()[0] ) );
  CHECK_THAT( xss[4], WithinRel( block.stoppingPowers()[1] ) );
  CHECK_THAT( xss[5], WithinRel( block.stoppingPowers()[2] ) );
  
  if ( xss.size() > 6 ) {
    
    CHECK_THAT( xss[6], WithinRel( block.corrections().value()[0] ) );
    CHECK_THAT( xss[7], WithinRel( block.corrections().value()[1] ) );
    CHECK_THAT( xss[8], WithinRel( block.corrections().value()[2] ) );
  } else {
    
    CHECK( std::nullopt == block.corrections() );
  }
}

RAD makeDummyBlock() {
  
  return RAD( { 0.0, 1.0 }, { 2.0, 3.0 } );
}
