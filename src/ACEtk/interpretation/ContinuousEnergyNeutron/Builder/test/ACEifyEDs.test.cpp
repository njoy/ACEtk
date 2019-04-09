
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
          ranges::view::single( 18 ),       // IDAT_1
          ranges::view::single( 2 ),        // N_R_1
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_1
          energies, probabilities,
          // Discrete photon energy
            ranges::view::single( 1 ),
            ranges::view::single( 3.14 ),
          ranges::view::single( 0 ),        // LNW_2
          ranges::view::single( 3 ),        // LAW_2
          ranges::view::single( 37 ),       // IDAT_2
          ranges::view::single( 2 ),        // N_R_2
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_2
          energies, probabilities,
          // Level scattering
            ranges::view::single( 2.765 ),
            ranges::view::single( 235.98 ),
        // Second set of distributions
          ranges::view::single( 58 ),       // LNW_1
          ranges::view::single( 3 ),        // LAW_1
          ranges::view::single( 56 ),       // IDAT_1
          ranges::view::single( 2 ),        // N_R_1
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_1
          energies, probabilities,
          // Level scattering
            ranges::view::single( 2.765 ),
            ranges::view::single( 235.98 ),
          ranges::view::single( 0 ),        // LNW_2
          ranges::view::single( 2 ),        // LAW_2
          ranges::view::single( 75 ),       // IDAT_2
          ranges::view::single( 2 ),        // N_R_2
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_2
          energies, probabilities,
          // Discrete photon energy
            ranges::view::single( 1 ),
            ranges::view::single( 3.14 )
      );

      Table::Data data{};
      CENBuilder.ACEifyEDs( EDs, data, 1, 2 );
      
      CHECK( ranges::equal( aceified, data.XSS() ) );
    }
  }
  GIVEN( "real-world example: 8017.800nc" ){

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
      CENBuilder.ACEifyEDs( EDs, data, 1, 2 );
      
      CHECK( ranges::equal( aceified, data.XSS() ) );
    }
  }
  GIVEN( "real-world example: 11022.800nc" ){
    auto aceified = std::vector< double >{
       1,          // LOCC_1 
       17,         // LOCC_2 
       35,         // LOCC_3 
       53,         // LOCC_4 
       64,         // LOCC_5 
       75,         // LOCC_6 
       86,         // LOCC_7 
       97,         // LOCC_8 
       108,        // LOCC_9 
       119,        // LOCC_10
       130,        // LOCC_11
       141,        // LOCC_12
       152,        // LOCC_13
       163,        // LOCC_14
       174         // LOCC_15
    };

    std::vector< std::vector< 
        ContinuousEnergyNeutron::Builder::EnergyDistribution > > EDs;
    std::vector< ContinuousEnergyNeutron::Builder::EnergyDistribution > inner;

    TestBuilder tb{ parentBuilder };

    { // MT=16
      std::vector< double > energies{ 11.0696, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      std::vector< double > theta{ 2.17669, 2.17669 };
      double U{ 10.584 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( energies ) )
          .effectiveTemperature( njoy::utility::copy( theta ) )
          .restrictionEnergy( U )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 9 ),                        // LAW_1
          ranges::view::single( 10 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( 2 ),                        // N_E
          energies, theta, ranges::view::single( U )
        )
      );
    }
    { // MT=22
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 11.0, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      std::vector< int > boundaries{ 2 };
      std::vector< int > schemes{ 5 };
      std::vector< double > theta{ 0.8, 1.2 };
      double U{ 10.518 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .evaporationSpectrum()
          .boundaries( njoy::utility::copy( boundaries ) )
          .schemes( njoy::utility::copy( schemes ) )
          .energies( njoy::utility::copy( energies ) )
          .effectiveTemperature( njoy::utility::copy( theta ) )
          .restrictionEnergy( U )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 9 ),                        // LAW_1
          ranges::view::single( 26 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( 1 ),                        // N_R
          boundaries, schemes,
          ranges::view::single( 2 ),                        // N_E
          energies, theta, ranges::view::single( U )
        )
      );
    }
    { // MT=28
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 7.0, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      std::vector< int > boundaries{ 2 };
      std::vector< int > schemes{ 5 };
      std::vector< double > theta{ 0.9, 1.1 };
      double U{ 6.6931 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .evaporationSpectrum()
          .boundaries( njoy::utility::copy( boundaries ) )
          .schemes( njoy::utility::copy( schemes ) )
          .energies( njoy::utility::copy( energies ) )
          .effectiveTemperature( njoy::utility::copy( theta ) )
          .restrictionEnergy( U )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 9 ),                        // LAW_1
          ranges::view::single( 44 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( 2 ),                        // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( 1 ),                        // N_R
          boundaries, schemes,
          ranges::view::single( 2 ),                        // N_E
          energies, theta, ranges::view::single( U )
        )
      );
    }
    { // MT=51
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 6.097365E-1, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 6.097364E-1 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 62 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=52
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 6.871301E-1, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 6.871301E-1 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 73 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=53
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 9.31757E-1, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 9.31757E-1 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 84 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=54
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 1.598075, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 1.5987074 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 95 ),                       // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=55
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 2.025832, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 2.025831 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 106 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=56
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 2.04152, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 2.041519 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 117 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=57
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 2.007499, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 2.007499 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 128 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=58
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 2.31344, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 2.31344 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 139 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=59
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 2.689953, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 2.689952 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 150 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=60
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 3.105160, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 3.105160 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 161 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=61
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 3.200333, 20.0 };
      std::vector< double > probabilities{ 1.0, 1.0 };
      double Q{ 3.200332 };
      double awr{ 0.9142246 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities ) )
        .levelScattering()
          .QValue( Q )
          .atomicWeightRatio( awr )
        .add(); // levelScattering

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 0 ),                        // LNW_1
          ranges::view::single( 3 ),                        // LAW_1
          ranges::view::single( 172 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities,
          // LAW data
          ranges::view::single( Q ),
          ranges::view::single( awr )
        )
      );

      inner.emplace_back( tb.construct() );
      EDs.emplace_back( std::move( inner ) );

    }
    { // MT=91
      inner = std::vector< 
          ContinuousEnergyNeutron::Builder::EnergyDistribution >{};

      std::vector< double > energies{ 3.519, 11.0, 11.0, 20.0 };
      std::vector< double > probabilities_1{ 1.0, 1.0, 0.0, 0.0 };
      std::vector< double > probabilities_2{ 0.0, 0.0, 1.0, 1.0 };
      std::vector< double > law_energies{ 3.519, 9.0, 20.0 };
      std::vector< double > theta{ 2.17669, 2.18846, 2.91265 };
      double U_1{ 3.519 };
      double U_2{ 0.6 };

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities_1 ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( law_energies ) )
          .effectiveTemperature( njoy::utility::copy( theta ) )
          .restrictionEnergy( U_1 )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );

      tb.energies( njoy::utility::copy( energies ) )
        .probabilities( njoy::utility::copy( probabilities_2 ) )
        .evaporationSpectrum()
          .energies( njoy::utility::copy( law_energies ) )
          .effectiveTemperature( njoy::utility::copy( theta ) )
          .restrictionEnergy( U_2 )
        .add(); // evaporationSpectrum

      inner.emplace_back( tb.construct() );

      EDs.emplace_back( std::move( inner ) );

      aceified |= ranges::action::push_back(
        ranges::view::concat(
          ranges::view::single( 196 ),                      // LNW_1
          ranges::view::single( 9 ),                        // LAW_1
          ranges::view::single( 187 ),                      // IDAT_1
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities_1,
          // LAW data
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( law_energies.size() ),      // N_E
          law_energies, theta, ranges::view::single( U_1 ),
          //
          ranges::view::single( 0 ),                        // LNW_2
          ranges::view::single( 9 ),                        // LAW_2
          ranges::view::single( 209 ),                      // IDAT_2
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( energies.size() ),          // N_E
          energies, probabilities_2,
          // LAW data
          ranges::view::single( 0 ),                        // N_R
          ranges::view::single( law_energies.size() ),      // N_E
          law_energies, theta, ranges::view::single( U_2 )
        )
      );

    }

    THEN( "the EnergyDistributions can be ACEified" ){

      Table::Data data{};
      int LED{ 1 };
      int NMT{ 15 };
      CENBuilder.ACEifyEDs( EDs, data, LED, NMT );
      
      CHECK( NMT == EDs.size() );
      CHECK( ranges::equal( aceified, data.XSS() ) );
    }
  }
} // SCENARIO
/* 11022.800nc
                  17                  35                  53                  64
                  75                  86                  97                 108
                 119                 130                 141                 152
                 163                 174                   0                   9
                  10                   0                   2   1.10696000000E+01
   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00                   0
                   2   1.10696000000E+01   2.00000000000E+01   2.17669000000E+00
   2.17669000000E+00   1.05840000000E+01                   0                   9
                  26                   0                   2   1.10000000000E+01
   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00                   1
                   2                   5                   2   1.10000000000E+01
   2.00000000000E+01   8.00000000000E-01   1.20000000000E+00   1.05180000000E+01
                   0                   9                  44                   0
                   2   7.00000000000E+00   2.00000000000E+01   1.00000000000E+00
   1.00000000000E+00                   1                   2                   5
                   2   7.00000000000E+00   2.00000000000E+01   9.00000000000E-01
   1.10000000000E+00   6.69310000000E+00                   0                   3
                  62                   0                   2   6.09736500000E-01
   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00   6.09736400000E-01
   9.14224600000E-01                   0                   3                  73
                   0                   2   6.87130100000E-01   2.00000000000E+01
   1.00000000000E+00   1.00000000000E+00   6.87130000000E-01   9.14224600000E-01
                   0                   3                  84                   0
                   2   9.31757000000E-01   2.00000000000E+01   1.00000000000E+00
   1.00000000000E+00   9.31756700000E-01   9.14224600000E-01                   0
                   3                  95                   0                   2
   1.59807500000E+00   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00
   1.59807400000E+00   9.14224600000E-01                   0                   3
                 106                   0                   2   2.02583200000E+00
   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00   2.02583100000E+00
   9.14224600000E-01                   0                   3                 117
                   0                   2   2.04152000000E+00   2.00000000000E+01
   1.00000000000E+00   1.00000000000E+00   2.04151900000E+00   9.14224600000E-01
                   0                   3                 128                   0
                   2   2.07499000000E+00   2.00000000000E+01   1.00000000000E+00
   1.00000000000E+00   2.07498600000E+00   9.14224600000E-01                   0
                   3                 139                   0                   2
   2.31344300000E+00   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00
   2.31344200000E+00   9.14224600000E-01                   0                   3
                 150                   0                   2   2.68995300000E+00
   2.00000000000E+01   1.00000000000E+00   1.00000000000E+00   2.68995200000E+00
   9.14224600000E-01                   0                   3                 161
                   0                   2   3.10516000000E+00   2.00000000000E+01
   1.00000000000E+00   1.00000000000E+00   3.10515800000E+00   9.14224600000E-01
                   0                   3                 172                   0
                   2   3.20033300000E+00   2.00000000000E+01   1.00000000000E+00
   1.00000000000E+00   3.20033200000E+00   9.14224600000E-01                 196
                   9                 187                   0                   4
   3.51900000000E+00   1.10000000000E+01   1.10000000000E+01   2.00000000000E+01
   1.00000000000E+00   1.00000000000E+00   0.00000000000E+00   0.00000000000E+00
                   0                   3   3.51900000000E+00   9.00000000000E+00
   2.00000000000E+01   2.17669000000E+00   2.18846000000E+00   2.91265000000E+00
   3.51900000000E+00                   0                   9                 209
                   0                   4   3.51900000000E+00   1.10000000000E+01
   1.10000000000E+01   2.00000000000E+01   0.00000000000E+00   0.00000000000E+00
   1.00000000000E+00   1.00000000000E+00                   0                   3
   3.51900000000E+00   9.00000000000E+00   2.00000000000E+01   2.17669000000E+00
   2.18846000000E+00   2.91265000000E+00   6.00000000000E-01                  13
                  16                   2                  -1                   0
                   0   1.50000100000E-02   1.70000000000E-02   2.00000000000E-02
*/
