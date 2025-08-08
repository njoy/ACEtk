// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ACEtk/ElectronTable.hpp"

// other includes
#include "ACEtk/fromFile.hpp"

// convenience typedefs
using namespace njoy::ACEtk;

void verifyTableEl( const ElectronTable& );
void verifyTableEl03( const ElectronTable& );

SCENARIO( "ElectronTable" ) {
  
  GIVEN( "valid data for an ElectronTable - el format" ) {
    
    WHEN( "constructing an ElectronTable from a Table" ) {
      
      auto table_to_move = fromFile( "26000.01e" );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy constructor" ) {
      
      ElectronTable table_to_copy( fromFile( "26000.01e" ) );
      ElectronTable table( table_to_copy );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move constructor" ) {
      
      ElectronTable table_to_move( fromFile( "26000.01e" ) );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy assignment" ) {
      
      ElectronTable table_to_copy( fromFile( "26000.01e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = table_to_copy;
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move assignment" ) {
      
      ElectronTable table_to_move( fromFile( "26000.01e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = std::move( table_to_move );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable from its components" ) {
      
      ElectronTable base_table( fromFile( "26000.01e" ) );
      ElectronTable table( 26, base_table.header(),
                           { 26054, 26056, 26057, 26058 },
                           { 53.476242, 55.454429, 56.446290, 57.435600 },
                           base_table.EKT(), base_table.RAD(),
                           base_table.MOT(), base_table.RLY(),
                           base_table.XSB(), base_table.CRB(),
                           base_table.HFB(), base_table.RKT(),
                           base_table.RKA(), base_table.OSC() );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl( table );
      }  // THEN
    }  // WHEN
  }  // GIVEN
  
  GIVEN( "valid data for an ElectronTable - el03 format" ) {
    
    WHEN( "constructing an ElectronTable from a Table" ) {
      
      auto table_to_move = fromFile( "6000.03e" );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy constructor" ) {
      
      ElectronTable table_to_copy( fromFile( "6000.03e" ) );
      ElectronTable table( table_to_copy );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move constructor" ) {
      
      ElectronTable table_to_move( fromFile( "6000.03e" ) );
      ElectronTable table( std::move( table_to_move ) );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the copy assignment" ) {
      
      ElectronTable table_to_copy( fromFile( "6000.03e" ) );
      ElectronTable table( fromFile( "6000.03e" ) );
      table = table_to_copy;
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable using the move assignment" ) {
      
      ElectronTable table_to_move( fromFile( "6000.03e" ) );
      ElectronTable table( fromFile( "26000.01e" ) );
      table = std::move( table_to_move );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
    
    WHEN( "constructing an ElectronTable from its components" ) {
      
      ElectronTable base_table( fromFile( "6000.03e" ) );
      njoy::tools::Log::info( "Base table type: {}", base_table.NEL() );
      ElectronTable table( 6, base_table.header(),
                           { 6012, 6013 },
                           { 11.896914, 12.891649 },
                           base_table.EKT(), base_table.RAD(),
                           base_table.MOT(), base_table.RLY(),
                           base_table.XSB(), base_table.CRB(),
                           base_table.HFB(), base_table.RKT(),
                           base_table.RKA(), base_table.OSC() );
      
      THEN( "an ElectronTable can be constructed "
            "and members can be tested" ) {
        
        verifyTableEl03( table );
      }  // THEN
    }  // WHEN
  }  // GIVEN
}  // SCENARIO

void verifyTableEl( const ElectronTable& table ) {
  
  auto base_table = fromFile( "26000.01e" );
  
  // verify table type
  CHECK( 3 != table.NEL() );
  CHECK( 3 != table.electronDataFormat() );
  
  // verify iz array
  CHECK( base_table.data().IZ().size() == table.data().IZ().size() );
  for ( unsigned int i = 0; i < table.data().IZ().size(); ++i ) {
    
    CHECK( base_table.data().IZ()[i] == table.data().IZ()[i] );
  }
  
  // verify aw array
  CHECK( base_table.data().AW().size() == table.data().AW().size() );
  for ( unsigned int i = 0; i < table.data().AW().size(); ++i ) {
    
    CHECK_THAT( base_table.data().AW()[i], WithinRel( table.data().AW()[i] ) );
  }
  
  // verify nxs array
  CHECK( base_table.data().NXS().size() == table.data().NXS().size() );
  for ( unsigned int i = 0; i < table.data().NXS().size(); ++i ) {
    
    CHECK( base_table.data().NXS()[i] == table.data().NXS()[i] );
  }
  
  // verify jxs array
  CHECK( base_table.data().JXS().size() == table.data().JXS().size() );
  for ( unsigned int i = 0; i < table.data().JXS().size(); ++i ) {
    
    CHECK( base_table.data().JXS()[i] == table.data().JXS()[i] );
  }
  
  // verify xxs array
  CHECK( base_table.data().XSS().size() == table.data().XSS().size() );
  for ( unsigned int i = 0; i < table.data().XSS().size(); ++i ) {
    
    CHECK_THAT( base_table.data().XSS()[i], WithinRel( table.data().XSS()[i] ) );
  }
  
  // verify ElectronTable interface for el format
  CHECK( "26000.01e" == table.ZAID() );
  CHECK_THAT( 55.366466, WithinRel( table.AWR() ) );
  CHECK_THAT( 55.366466, WithinRel( table.atomicWeightRatio() ) );
  CHECK_THAT( 0.0, WithinRel( table.TEMP() ) );
  CHECK_THAT( 0.0, WithinRel( table.temperature() ) );
  CHECK( "11/16/88" == table.date() );
  
  CHECK( 478 == table.length() );
  CHECK( 26 == table.Z() );
  CHECK( 26 == table.atomNumber() );
  CHECK( 0 == table.S() );
  CHECK( 0 == table.isomericState() );
  CHECK( 0 == table.A() );
  CHECK( 0 == table.massNumber() );
  
  CHECK( 49 == table.NRAD() );
  CHECK( 49 == table.numberRadiationStoppingPoints() );
  CHECK( 18 == table.NMOT() );
  CHECK( 18 == table.numberMottCorrectionPoints() );
  CHECK( 0 == table.NEB() );
  CHECK( 0 == table.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 0 == table.NPB() );
  CHECK( 0 == table.numberPhotonBremsstrahlungRatioPoints() );
  CHECK( 32 == table.NCRB() );
  CHECK( 32 == table.numberBremsstrahlungCorrectionPoints() );
  CHECK( 39 == table.NHFB() );
  CHECK( 39 == table.numberBremsstrahlungHighFrequencyPoints() );
  CHECK( 0 == table.NRKT() );
  CHECK( 0 == table.numberBremsstrahlungEnergyPoints() );
  CHECK( 0 == table.NRKA() );
  CHECK( 0 == table.numberBremsstrahlungAngularPoints() );
  CHECK( 0 == table.NOSC() );
  CHECK( 0 == table.numberOscillatorPoints() );
  
  // EKT block
  CHECK_THAT( 7.112, WithinRel( table.EKT().EDG() ) );
  CHECK_THAT( 7.112, WithinRel( table.EKT().kEdgeEnergy() ) );
  CHECK_THAT( 6.47, WithinRel( table.EKT().EEK() ) );
  CHECK_THAT( 6.47, WithinRel( table.EKT().kXrayEmissionEnergy() ) );
  
  CHECK( true == table.EKT().upperBremsstrahlungTransitionEnergy().has_value() );
  CHECK_THAT( 0.9877, WithinRel( table.EKT().upperBremsstrahlungTransitionEnergy().value() ) );
  CHECK( true == table.EKT().lowerBremsstrahlungTransitionEnergy().has_value() );
  CHECK_THAT( 0.9525, WithinRel( table.EKT().lowerBremsstrahlungTransitionEnergy().value() ) );
  
  // RAD block
  CHECK( 49 == table.RAD().NRAD() );
  CHECK( 49 == table.RAD().numberEnergyPoints() );
  
  CHECK( 49 == table.RAD().energies().size() );
  CHECK_THAT( 999.99994, WithinRel( table.RAD().energies().front() ) );
  CHECK_THAT( 0.001, WithinRel( table.RAD().energies().back() ) );
  
  CHECK( 49 == table.RAD().stoppingPowers().size() );
  CHECK_THAT( 15.9898, WithinRel( table.RAD().stoppingPowers().front() ) );
  CHECK_THAT( 7.3423, WithinRel( table.RAD().stoppingPowers().back() ) );
  
  // MOT block
  CHECK( 18 == table.MOT().NMOT() );
  CHECK( 18 == table.MOT().numberEnergyPoints() );
  
  CHECK( 18 == table.MOT().energies().size() );
  CHECK_THAT( 1.0e3, WithinRel( table.MOT().energies().front() ) );
  CHECK_THAT( 1.0e-4, WithinRel( table.MOT().energies().back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 1 ).size() );
  CHECK_THAT( 1.0, WithinRel( table.MOT().mottScatteringCorrection( 1 ).front() ) );
  CHECK_THAT( 1.0, WithinRel( table.MOT().mottScatteringCorrection( 1 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 2 ).size() );
  CHECK_THAT( 1.03811, WithinRel( table.MOT().mottScatteringCorrection( 2 ).front() ) );
  CHECK_THAT( 1.00076, WithinRel( table.MOT().mottScatteringCorrection( 2 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 3 ).size() );
  CHECK_THAT( 0.68019, WithinRel( table.MOT().mottScatteringCorrection( 3 ).front() ) );
  CHECK_THAT( 1.00452, WithinRel( table.MOT().mottScatteringCorrection( 3 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 4 ).size() );
  CHECK_THAT( 0.21082, WithinRel( table.MOT().mottScatteringCorrection( 4 ).front() ) );
  CHECK_THAT( 1.00345, WithinRel( table.MOT().mottScatteringCorrection( 4 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 5 ).size() );
  CHECK_THAT( 0.0, WithinRel( table.MOT().mottScatteringCorrection( 5 ).front() ) );
  CHECK_THAT( 1.07119, WithinRel( table.MOT().mottScatteringCorrection( 5 ).back() ) );
  
  // RLY block
  CHECK_THAT( 256.0, WithinRel( table.RLY().energy( 1 ) ) );
  CHECK_THAT( 2.75394535e-6, WithinRel( table.RLY().parameterSet( 1 )[1] ) );
  CHECK_THAT( 6.64764995e-5, WithinRel( table.RLY().parameterSet( 1 )[13] ) );
  
  CHECK_THAT( 128.0, WithinRel( table.RLY().energy( 2 ) ) );
  CHECK_THAT( 9.44261590e-6, WithinRel( table.RLY().parameterSet( 2 )[1] ) );
  CHECK_THAT( 1.58986771e-4, WithinRel( table.RLY().parameterSet( 2 )[13] ) );
  
  CHECK_THAT( 64.0, WithinRel( table.RLY().energy( 3 ) ) );
  CHECK_THAT( 3.42943297e-5, WithinRel( table.RLY().parameterSet( 3 )[1] ) );
  CHECK_THAT( 3.35456602e-4, WithinRel( table.RLY().parameterSet( 3 )[13] ) );
  
  CHECK_THAT( 32.0, WithinRel( table.RLY().energy( 4 ) ) );
  CHECK_THAT( 1.29874745e-4, WithinRel( table.RLY().parameterSet( 4 )[1] ) );
  CHECK_THAT( 2.80010454e-4, WithinRel( table.RLY().parameterSet( 4 )[13] ) );
  
  CHECK_THAT( 16.0, WithinRel( table.RLY().energy( 5 ) ) );
  CHECK_THAT( 5.04536727e-4, WithinRel( table.RLY().parameterSet( 5 )[1] ) );
  CHECK_THAT( 6.39633577e-4, WithinRel( table.RLY().parameterSet( 5 )[13] ) );
  
  CHECK_THAT( 8.0, WithinRel( table.RLY().energy( 6 ) ) );
  CHECK_THAT( 1.98786332e-3, WithinRel( table.RLY().parameterSet( 6 )[1] ) );
  CHECK_THAT( 9.75920081e-4, WithinRel( table.RLY().parameterSet( 6 )[13] ) );
  
  CHECK_THAT( 4.0, WithinRel( table.RLY().energy( 7 ) ) );
  CHECK_THAT( 7.89052648e-3, WithinRel( table.RLY().parameterSet( 7 )[1] ) );
  CHECK_THAT( 1.78058167e-3, WithinRel( table.RLY().parameterSet( 7 )[13] ) );
  
  CHECK_THAT( 2.0, WithinRel( table.RLY().energy( 8 ) ) );
  CHECK_THAT( 3.14398926e-2, WithinRel( table.RLY().parameterSet( 8 )[1] ) );
  CHECK_THAT( 3.72055509e-3, WithinRel( table.RLY().parameterSet( 8 )[13] ) );
  
  CHECK_THAT( 1.0, WithinRel( table.RLY().energy( 9 ) ) );
  CHECK_THAT( 1.25514784e-1, WithinRel( table.RLY().parameterSet( 9 )[1] ) );
  CHECK_THAT( 7.22353160e-3, WithinRel( table.RLY().parameterSet( 9 )[13] ) );
  
  // XSB block
  CHECK( false == table.XSB().has_value() );
  
  // CRB block
  CHECK( true == table.CRB().has_value() );
  auto crb = table.CRB().value();
  
  CHECK( 32 == crb.NCRB() );
  CHECK( 32 == crb.numberEnergyPoints() );
  
  CHECK_THAT( 1.0e3, WithinRel( crb.energies().front() ) );
  CHECK_THAT( 0.5, WithinRel( crb.energies()[16] ) );
  CHECK_THAT( 9.9e-4, WithinRel( crb.energies().back() ) );
  
  CHECK_THAT( 1.0, WithinRel( crb.corrections().front() ) );
  CHECK_THAT( 1.0507, WithinRel( crb.corrections()[16] ) );  // Check a value != 1.0
  CHECK_THAT( 1.0, WithinRel( crb.corrections().back() ) );
  
  // HFB block
  CHECK( true == table.HFB().has_value() );
  auto hfb = table.HFB().value();
  
  CHECK( 39 == hfb.NHFB() );
  CHECK( 39 == hfb.numberEnergyPoints() );
  
  CHECK_THAT( 1.0e3, WithinRel( hfb.energies().front() ) );
  CHECK_THAT( 9.9e-4, WithinRel( hfb.energies().back() ) );
  
  CHECK_THAT( 0.73338, WithinRel( hfb.crossSections().front() ) );
  CHECK_THAT( 2.3987776e3, WithinRel( hfb.crossSections().back() ) );
  
  // RKT block
  CHECK( false == table.RKT().has_value() );
  
  // RKA block
  CHECK( false == table.RKA().has_value() );
  
  // OSC block
  CHECK( false == table.OSC().has_value() );
}

void verifyTableEl03( const ElectronTable& table ) {
  
  auto base_table = fromFile( "6000.03e" );
  
  // verify table type
  CHECK( 3 == table.NEL() );
  CHECK( 3 == table.electronDataFormat() );
  
  // verify iz array
  CHECK( base_table.data().IZ().size() == table.data().IZ().size() );
  for ( unsigned int i = 0; i < table.data().IZ().size(); ++i ) {
    
    CHECK( base_table.data().IZ()[i] == table.data().IZ()[i] );
  }
  
  // verify aw array
  CHECK( base_table.data().AW().size() == table.data().AW().size() );
  for ( unsigned int i = 0; i < table.data().AW().size(); ++i ) {
    
    CHECK_THAT( base_table.data().AW()[i], WithinRel( table.data().AW()[i] ) );
  }
  
  // verify nxs array
  CHECK( base_table.data().NXS().size() == table.data().NXS().size() );
  for ( unsigned int i = 0; i < table.data().NXS().size(); ++i ) {
    
    CHECK( base_table.data().NXS()[i] == table.data().NXS()[i] );
  }
  
  // verify jxs array
  CHECK( base_table.data().JXS().size() == table.data().JXS().size() );
  for ( unsigned int i = 0; i < table.data().JXS().size(); ++i ) {
    
    CHECK( base_table.data().JXS()[i] == table.data().JXS()[i] );
  }
  
  // verify xxs array
  CHECK( base_table.data().XSS().size() == table.data().XSS().size() );
  for ( unsigned int i = 0; i < table.data().XSS().size(); ++i ) {
    
    CHECK_THAT( base_table.data().XSS()[i], WithinRel( table.data().XSS()[i] ) );
  }
  
  // verify ElectronTable interface for el03 format
  CHECK( "6000.03e" == table.ZAID() );
  CHECK_THAT( 11.907955, WithinRel( table.AWR() ) );
  CHECK_THAT( 11.907955, WithinRel( table.atomicWeightRatio() ) );
  CHECK_THAT( 0.0, WithinRel( table.TEMP() ) );
  CHECK_THAT( 0.0, WithinRel( table.temperature() ) );
  CHECK( "6/6/98" == table.date() );
  
  CHECK( 2333 == table.length() );
  CHECK( 6 == table.Z() );
  CHECK( 6 == table.atomNumber() );
  CHECK( 0 == table.S() );
  CHECK( 0 == table.isomericState() );
  CHECK( 0 == table.A() );
  CHECK( 0 == table.massNumber() );
  
  CHECK( 57 == table.NRAD() );
  CHECK( 57 == table.numberRadiationStoppingPoints() );
  CHECK( 18 == table.NMOT() );
  CHECK( 18 == table.numberMottCorrectionPoints() );
  CHECK( 57 == table.NEB() );
  CHECK( 57 == table.numberElectronBremsstrahlungEnergyPoints() );
  CHECK( 30 == table.NPB() );
  CHECK( 30 == table.numberPhotonBremsstrahlungRatioPoints() );
  CHECK( 0 == table.NCRB() );
  CHECK( 0 == table.numberBremsstrahlungCorrectionPoints() );
  CHECK( 0 == table.NHFB() );
  CHECK( 0 == table.numberBremsstrahlungHighFrequencyPoints() );
  CHECK( 89 == table.NRKT() );
  CHECK( 89 == table.numberBremsstrahlungEnergyPoints() );
  CHECK( 34 == table.NRKA() );
  CHECK( 34 == table.numberBremsstrahlungAngularPoints() );
  CHECK( 3 == table.NOSC() );
  CHECK( 3 == table.numberOscillatorPoints() );
  
  // EKT block
  CHECK_THAT( 0.2838, WithinRel( table.EKT().EDG() ) );
  CHECK_THAT( 0.2838, WithinRel( table.EKT().kEdgeEnergy() ) );
  CHECK_THAT( 0.2838, WithinRel( table.EKT().EEK() ) );
  CHECK_THAT( 0.2838, WithinRel( table.EKT().kXrayEmissionEnergy() ) );
  
  CHECK( false == table.EKT().upperBremsstrahlungTransitionEnergy().has_value() );
  CHECK( false == table.EKT().lowerBremsstrahlungTransitionEnergy().has_value() );
  
  // RAD block
  CHECK( 57 == table.RAD().NRAD() );
  CHECK( 57 == table.RAD().numberEnergyPoints() );
  
  CHECK( 57 == table.RAD().energies().size() );
  CHECK_THAT( 1.0e4, WithinRel( table.RAD().energies().front() ) );
  CHECK_THAT( 0.001, WithinRel( table.RAD().energies().back() ) );
  
  CHECK( 57 == table.RAD().stoppingPowers().size() );
  CHECK_THAT( 18.59821, WithinRel( table.RAD().stoppingPowers().front() ) );
  CHECK_THAT( 4.68083, WithinRel( table.RAD().stoppingPowers().back() ) );
  
  CHECK( 57 == table.RAD().corrections().value().size() );
  CHECK_THAT( 1.16871, WithinRel( table.RAD().corrections().value().front() ) );
  CHECK_THAT( 0.00103, WithinRel( table.RAD().corrections().value().back() ) );
  
  // MOT block
  CHECK( 18 == table.MOT().NMOT() );
  CHECK( 18 == table.MOT().numberEnergyPoints() );
  
  CHECK( 18 == table.MOT().energies().size() );
  CHECK_THAT( 1.0e3, WithinRel( table.MOT().energies().front() ) );
  CHECK_THAT( 1.0e-4, WithinRel( table.MOT().energies().back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 1 ).size() );
  CHECK_THAT( 1.0, WithinRel( table.MOT().mottScatteringCorrection( 1 ).front() ) );
  CHECK_THAT( 1.0, WithinRel( table.MOT().mottScatteringCorrection( 1 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 2 ).size() );
  CHECK_THAT( 0.88845, WithinRel( table.MOT().mottScatteringCorrection( 2 ).front() ) );
  CHECK_THAT( 0.99992, WithinRel( table.MOT().mottScatteringCorrection( 2 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 3 ).size() );
  CHECK_THAT( 0.5311, WithinRel( table.MOT().mottScatteringCorrection( 3 ).front() ) );
  CHECK_THAT( 1.00099, WithinRel( table.MOT().mottScatteringCorrection( 3 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 4 ).size() );
  CHECK_THAT( 0.15641, WithinRel( table.MOT().mottScatteringCorrection( 4 ).front() ) );
  CHECK_THAT( 1.00357, WithinRel( table.MOT().mottScatteringCorrection( 4 ).back() ) );
  
  CHECK( 18 == table.MOT().mottScatteringCorrection( 5 ).size() );
  CHECK_THAT( 0.0, WithinRel( table.MOT().mottScatteringCorrection( 5 ).front() ) );
  CHECK_THAT( 1.005, WithinRel( table.MOT().mottScatteringCorrection( 5 ).back() ) );
  
  // RLY block
  CHECK_THAT( 256.0, WithinRel( table.RLY().energy( 1 ) ) );
  CHECK_THAT( 1.46659811e-7, WithinRel( table.RLY().parameterSet( 1 )[1] ) );
  CHECK_THAT( 6.64745837e-5, WithinRel( table.RLY().parameterSet( 1 )[13] ) );
  
  CHECK_THAT( 128.0, WithinRel( table.RLY().energy( 2 ) ) );
  CHECK_THAT( 5.02861202e-7, WithinRel( table.RLY().parameterSet( 2 )[1] ) );
  CHECK_THAT( 1.45304229e-4, WithinRel( table.RLY().parameterSet( 2 )[13] ) );
  
  CHECK_THAT( 64.0, WithinRel( table.RLY().energy( 3 ) ) );
  CHECK_THAT( 1.82632525e-6, WithinRel( table.RLY().parameterSet( 3 )[1] ) );
  CHECK_THAT( 3.04942194e-4, WithinRel( table.RLY().parameterSet( 3 )[13] ) );
  
  CHECK_THAT( 32.0, WithinRel( table.RLY().energy( 4 ) ) );
  CHECK_THAT( 6.91640655e-6, WithinRel( table.RLY().parameterSet( 4 )[1] ) );
  CHECK_THAT( 5.98302116e-4, WithinRel( table.RLY().parameterSet( 4 )[13] ) );
  
  CHECK_THAT( 16.0, WithinRel( table.RLY().energy( 5 ) ) );
  CHECK_THAT( 2.68688198e-5, WithinRel( table.RLY().parameterSet( 5 )[1] ) );
  CHECK_THAT( 1.18037386e-3, WithinRel( table.RLY().parameterSet( 5 )[13] ) );
  
  CHECK_THAT( 8.0, WithinRel( table.RLY().energy( 6 ) ) );
  CHECK_THAT( 1.05862544e-4, WithinRel( table.RLY().parameterSet( 6 )[1] ) );
  CHECK_THAT( 4.46677165e-4, WithinRel( table.RLY().parameterSet( 6 )[13] ) );
  
  CHECK_THAT( 4.0, WithinRel( table.RLY().energy( 7 ) ) );
  CHECK_THAT( 4.20205552e-4, WithinRel( table.RLY().parameterSet( 7 )[1] ) );
  CHECK_THAT( 1.90032505e-3, WithinRel( table.RLY().parameterSet( 7 )[13] ) );
  
  CHECK_THAT( 2.0, WithinRel( table.RLY().energy( 8 ) ) );
  CHECK_THAT( 1.67431380e-3, WithinRel( table.RLY().parameterSet( 8 )[1] ) );
  CHECK_THAT( 3.82060130e-3, WithinRel( table.RLY().parameterSet( 8 )[13] ) );
  
  CHECK_THAT( 1.0, WithinRel( table.RLY().energy( 9 ) ) );
  CHECK_THAT( 6.68421925e-3, WithinRel( table.RLY().parameterSet( 9 )[1] ) );
  CHECK_THAT( 5.59245416e-3, WithinRel( table.RLY().parameterSet( 9 )[13] ) );
  
  // XSB block
  CHECK( true == table.XSB().has_value() );
  auto xsb = table.XSB().value();
  
  CHECK( 57 == xsb.NEB() );
  CHECK( 57 == xsb.numberElectronEnergies() );
  CHECK( 30 == xsb.NPB() );
  CHECK( 30 == xsb.numberPhotonRatios() );
  CHECK( 1710 == xsb.numberCrossSections() );
  
  CHECK_THAT( 0.001, WithinRel( xsb.electronEnergy( 1 ) ) );
  CHECK_THAT( 0.001, WithinRel( xsb.electronEnergies().front() ) );
  CHECK_THAT( 1.0e4, WithinRel( xsb.electronEnergy( 57 ) ) );
  CHECK_THAT( 1.0e4, WithinRel( xsb.electronEnergies().back() ) );
  
  CHECK_THAT( 0.0, WithinRel( xsb.photonRatio( 1 ) ) );
  CHECK_THAT( 0.0, WithinRel( xsb.photonRatios().front() ) );
  CHECK_THAT( 1.0, WithinRel( xsb.photonRatio( 30 ) ) );
  CHECK_THAT( 1.0, WithinRel( xsb.photonRatios().back() ) );
  
  CHECK_THAT( 5.33622e-3, WithinRel( xsb.crossSection( 1, 1 ) ) );
  CHECK_THAT( 5.33622e-3, WithinRel( xsb.crossSections( 1 ).front() ) );
  CHECK_THAT( 5.33622e-3, WithinRel( xsb.crossSectionData()[0] ) );
  
  CHECK_THAT( 5.1576e-3, WithinRel( xsb.crossSection( 1, 30 ) ) );
  CHECK_THAT( 5.1576e-3, WithinRel( xsb.crossSections( 1 ).back() ) );
  CHECK_THAT( 5.1576e-3, WithinRel( xsb.crossSectionData()[1653] ) );
  
  CHECK_THAT( 1.748959e-2, WithinRel( xsb.crossSection( 57, 1 ) ) );
  CHECK_THAT( 1.748959e-2, WithinRel( xsb.crossSections( 57 ).front() ) );
  CHECK_THAT( 1.748959e-2, WithinRel( xsb.crossSectionData()[56] ) );
  
  CHECK_THAT( 2.7055e-4, WithinRel( xsb.crossSection( 57, 30 ) ) );
  CHECK_THAT( 2.7055e-4, WithinRel( xsb.crossSections( 57 ).back() ) );
  CHECK_THAT( 2.7055e-4, WithinRel( xsb.crossSectionData()[1709] ) );
  
  // CRB block
  CHECK( false == table.CRB().has_value() );
  
  // HFB block
  CHECK( false == table.HFB().has_value() );
  
  // RKT block
  CHECK( true == table.RKT().has_value() );
  auto rkt = table.RKT().value();
  
  CHECK( 89 == rkt.NRKT() );
  CHECK( 89 == rkt.numberPhotonEnergyRatios() );
  
  CHECK_THAT( 1.0e-6, WithinRel( rkt.photonEnergyRatios().front() ) );
  CHECK_THAT( 1.0, WithinRel( rkt.photonEnergyRatios().back() ) );
  
  // RKA block
  CHECK( true == table.RKA().has_value() );
  auto rka = table.RKA().value();
  
  CHECK( 34 == rka.NRKA() );
  CHECK( 34 == rka.numberPhotonEnergyRatios() );
  
  CHECK_THAT( 0.9999, WithinRel( rka.photonEnergyRatios().front() ) );
  CHECK_THAT( 1.0e-6, WithinRel( rka.photonEnergyRatios().back() ) );
  
  // OSC block
  CHECK( true == table.OSC().has_value() );
  auto osc = table.OSC().value();
  
  CHECK( 3 == osc.NOSC() );
  CHECK( 3 == osc.numberOscillators() );
  
  CHECK_THAT( 2.0, WithinRel( osc.occupationNumbers().front() ) );
  CHECK_THAT( -2.0, WithinRel( osc.occupationNumbers().back() ) );
  
  CHECK_THAT( 288.0, WithinRel( osc.bindingEnergies().front() ) );
  CHECK_THAT( 11.26, WithinRel( osc.bindingEnergies().back() ) );
}
