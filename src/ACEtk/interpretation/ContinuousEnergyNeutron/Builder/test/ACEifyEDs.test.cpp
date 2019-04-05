
#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Complete ContinuousEnergyNeutron::Builder::ACEifyEDs" ){
  ContinuousEnergyNeutron::Builder CENBuilder;
  using ParentBuilder = decltype( CENBuilder.reaction( 14 ) );

  ParentBuilder parentBuilder{ CENBuilder, 14 };
  using EDBuilder = decltype( parentBuilder.energyDistribution() );

  struct TestBuilder : public EDBuilder {
    using EDBuilder::construct;
    using EDBuilder::EDBuilder;
  };

  /*
  GIVEN( "made-up example" ){
    std::vector< int > boundaries{ 0, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
    std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

    std::vector< std::vector< 
        ContinuousEnergyNeutron::Builder::EnergyDistribution > > EDs;
    std::vector< ContinuousEnergyNeutron::Builder::EnergyDistribution > inner;

    {
      TestBuilder tb{ parentBuilder };
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .discretePhotonEnergy()
          .energy( 3.14 )
          .primaryFlag( 1 )
        .add(); // discretePhotonEnergy

      inner.emplace_back( tb.construct() );

      tb = TestBuilder{ parentBuilder };
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .atomicWeightRatio( 235.98 )
          .QValue( 2.765 )
        .add(); // levelScattering

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      tb = TestBuilder{ parentBuilder };
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .atomicWeightRatio( 235.98 )
          .QValue( 2.765 )
        .add(); // levelScattering

      inner.emplace_back( tb.construct() );

      tb = TestBuilder{ parentBuilder };
      tb.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .discretePhotonEnergy()
          .energy( 3.14 )
          .primaryFlag( 1 )
        .add(); // discretePhotonEnergy

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( inner );
    }

    THEN( "the EnergyDistributions can be ACEified" ){
      auto aceified = ranges::view::concat(
        ranges::view::single( 1 ),          // LOCC_1
        ranges::view::single( 39 ),         // LOCC_2
        // First set of distributions
          ranges::view::single( 20 ),       // LNW_1
          ranges::view::single( 2 ),        // LAW_1
          ranges::view::single( 21 ),       // IDAT_1
          ranges::view::single( 2 ),        // N_R_1
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_1
          energies, probabilities,
          // Discrete photon energy
            ranges::view::single( 1 ),
            ranges::view::single( 3.14 ),
          ranges::view::single( 0 ),        // LNW_2
          ranges::view::single( 3 ),        // LAW_2
          ranges::view::single( 38 ),       // IDAT_2
          ranges::view::single( 2 ),        // N_R_2
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_2
          energies, probabilities,
          // Level scattering
            ranges::view::single( 2.765 ),
            ranges::view::single( 235.98 ),
        // Second set of distributions
          ranges::view::single( 18 ),       // LNW_1
          ranges::view::single( 3 ),        // LAW_1
          ranges::view::single( 16 ),       // IDAT_1
          ranges::view::single( 2 ),        // N_R_1
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_1
          energies, probabilities,
          // Level scattering
            ranges::view::single( 2.765 ),
            ranges::view::single( 235.98 ),
          ranges::view::single( 0 ),        // LNW_2
          ranges::view::single( 2 ),        // LAW_2
          ranges::view::single( 36 ),       // IDAT_2
          ranges::view::single( 2 ),        // N_R_2
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_2
          energies, probabilities,
          // Discrete photon energy
            ranges::view::single( 1 ),
            ranges::view::single( 3.14 )
      );

      Table::Data data{};
      data.XSS() |= ranges::action::push_back(
        ranges::view::repeat_n( 0, EDs.size() )
      );
      CENBuilder.ACEifyEDs( EDs, data, 1, 3 );
      
      njoy::Log::info( "aceified: {}", aceified | ranges::view::all );
      njoy::Log::info( "data.XSS: {}", data.XSS() | ranges::view::all );

      CHECK( ranges::equal( aceified, data.XSS() ) );
    }
  }
  */

  GIVEN( "real-world example" ){
    // This comes from 8017.800nc

    std::vector< std::vector< 
        ContinuousEnergyNeutron::Builder::EnergyDistribution > > EDs;
    std::vector< ContinuousEnergyNeutron::Builder::EnergyDistribution > inner;

    TestBuilder tb{ parentBuilder };

    std::vector< double > energies_1{ 4.39021, 4.39021, 20.0 };
    std::vector< double > probabilities_1{ 0.0, 0.5, 0.5 };
    std::vector< double > Law9_1Energies{ 
      4.39021 , 7.   , 8.   , 9.   , 10.0 , 11.0 , 12.0 , 13.0 , 
      14.0    , 14.5 , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0
    };

    std::vector< double > Law9_1Theta{ 
      3.719790E-01, 3.719790E-01, 3.778070E-01, 3.920370E-01,
      4.057470E-01, 4.189910E-01, 4.318120E-01, 4.442490E-01,
      4.563340E-01, 4.622540E-01, 4.680960E-01, 4.79560E-01,
      4.907460E-01, 5.016740E-01, 5.123620E-01, 5.228240E-01 
    };
    double U_1{ 4.1443 };

    std::vector< double > Law9_2Energies{ 
      4.390210 , 9.0  , 10.0 , 11.0 , 12.0 , 13.0 , 14.0 , 
      14.5     , 15.0 , 16.0 , 17.0 , 18.0 , 19.0 , 20.0
    };

    std::vector< double > Law9_2Theta{ 
      3.927790E-01, 3.927790E-01, 4.067020E-01, 4.203740E-01,
      4.336080E-01, 4.464450E-01, 4.584190E-01,
      4.650280E-01, 4.710570E-01, 4.828870E-01, 4.94430E-01,
      5.057060E-01, 5.167330E-01, 5.275280E-01
    };
    double U_2{ 4.1443 };

    std::vector< double > energies_2{ 6.731, 6.731, 20.0 };
    std::vector< double > probabilities_2{ 0.0, 1.0, 1.0 };
    std::vector< double > Law9_3Energies{ 
      6.731 , 13.0 , 14.0 , 14.5 , 15.0 , 
      16.0  , 17.0 , 18.0 , 19.0 , 20.0
    };

    std::vector< double > Law9_3Theta{ 
      4.163360E-01 , 4.163360E-01 , 4.261050E-01 , 4.33280E-01  , 4.403330E-01 , 
      4.540970E-01 , 4.674390E-01 , 4.803950E-01 , 4.929970E-01 , 5.052740E-01
    };
    double U_3{ 6.35303 };
    {

      tb.energies( njoy::utility::copy( energies_1 ) )
        .probabilities( njoy::utility::copy( probabilities_1 ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( Law9_1Energies ) )
          .effectiveTemperature( njoy::utility::copy( Law9_1Theta ) )
          .restrictionEnergy( U_1 )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );

      tb.energies( njoy::utility::copy( energies_1 ) )
        .probabilities( njoy::utility::copy( probabilities_1 ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( Law9_2Energies ) )
          .effectiveTemperature( njoy::utility::copy( Law9_2Theta ) )
          .restrictionEnergy( U_2 )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      tb.energies( njoy::utility::copy( energies_2 ) )
        .probabilities( njoy::utility::copy( probabilities_2 ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( Law9_3Energies ) )
          .effectiveTemperature( njoy::utility::copy( Law9_3Theta ) )
          .restrictionEnergy( U_3 )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }

    THEN( "the EnergyDistributions can be ACEified" ){
      auto aceified = ranges::view::concat(
        ranges::view::single( 1 ),          // LOCC_1
        ranges::view::single( 89 ),         // LOCC_2
        // Reaction 1--MT16
        ranges::view::single( 47 ),         // LNW_1
        ranges::view::single( 9 ),          // LAW_1
        ranges::view::single( 12 ),         // IDAT_1
        ranges::view::single( 0 ),          // N_R
        ranges::view::single( 3 ),          // N_E
        energies_1, probabilities_1,
          // LAW 9
          ranges::view::single( 0 ),          // N_R
          ranges::view::single( 16 ),          // N_E
          Law9_1Energies, Law9_1Theta, 
          ranges::view::single( U_1 ),
        ranges::view::single( 0 ),          // LNW_2
        ranges::view::single( 9 ),          // LAW_2
        ranges::view::single( 58 ),         // IDAT_2
        ranges::view::single( 0 ),          // N_R
        ranges::view::single( 3 ),          // N_E
        energies_1, probabilities_1,
          // LAW 9
          ranges::view::single( 0 ),          // N_R
          ranges::view::single( 14 ),          // N_E
          Law9_2Energies, Law9_2Theta, 
          ranges::view::single( U_2 ),
        // Reaction 2--MT22
        ranges::view::single( 0 ),         // LNW_1
        ranges::view::single( 9 ),          // LAW_1
        ranges::view::single( 100 ),         // IDAT_1
        ranges::view::single( 0 ),          // N_R
        ranges::view::single( 3 ),          // N_E
        energies_2, probabilities_2,
          // LAW 9
          ranges::view::single( 0 ),          // N_R
          ranges::view::single( 10 ),          // N_E
          Law9_3Energies, Law9_3Theta, 
          ranges::view::single( U_3 )
      );

      Table::Data data{};
      data.XSS() |= ranges::action::push_back(
        ranges::view::repeat_n( 0, EDs.size() )
      );
      CENBuilder.ACEifyEDs( EDs, data, 1, 3 );
      
      CHECK( ranges::equal( aceified, data.XSS() ) );
    }
  }
} // SCENARIO
