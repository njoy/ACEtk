
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
      std::vector< double > aceified{};
        aceified.push_back( 1 );          // LOCC_1
        aceified.push_back( 39 );         // LOCC_2
        // First set of distributions
          aceified.push_back( 20 );       // LNW_1
          aceified.push_back( 2 );        // LAW_1
          aceified.push_back( 18 );       // IDAT_1
          aceified.push_back( 2 );        // N_R_1
          aceified |= ranges::action::push_back( boundaries );
          aceified |= ranges::action::push_back( schemes );
          aceified.push_back( 4 );        // N_E_1
          aceified |= ranges::action::push_back( energies );
          aceified |= ranges::action::push_back( probabilities );
          // Discrete photon energy
            aceified.push_back( 1 );
            aceified.push_back( 3.14 );
          aceified.push_back( 0 );        // LNW_2
          aceified.push_back( 3 );        // LAW_2
          aceified.push_back( 37 );       // IDAT_2
          aceified.push_back( 2 );        // N_R_2
          aceified |= ranges::action::push_back( boundaries );
          aceified |= ranges::action::push_back( schemes );
          aceified.push_back( 4 );        // N_E_2
          aceified |= ranges::action::push_back( energies );
          aceified |= ranges::action::push_back( probabilities );
          // Level scattering
            aceified.push_back( 2.765 );
            aceified.push_back( 235.98 );
        // Second set of distributions
          aceified.push_back( 58 );       // LNW_1
          aceified.push_back( 3 );        // LAW_1
          aceified.push_back( 56 );       // IDAT_1
          aceified.push_back( 2 );        // N_R_1
          aceified |= ranges::action::push_back( boundaries );
          aceified |= ranges::action::push_back( schemes );
          aceified.push_back( 4 );        // N_E_1
          aceified |= ranges::action::push_back( energies );
          aceified |= ranges::action::push_back( probabilities );
          // Level scattering
            aceified.push_back( 2.765 );
            aceified.push_back( 235.98 );
          aceified.push_back( 0 );        // LNW_2
          aceified.push_back( 2 );        // LAW_2
          aceified.push_back( 75 );       // IDAT_2
          aceified.push_back( 2 );        // N_R_2
          aceified |= ranges::action::push_back( boundaries );
          aceified |= ranges::action::push_back( schemes );
          aceified.push_back( 4 );        // N_E_2
          aceified |= ranges::action::push_back( energies );
          aceified |= ranges::action::push_back( probabilities );
          // Discrete photon energy
            aceified.push_back( 1 );
            aceified.push_back( 3.14 );

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
      std::vector< double > aceified{};
        aceified.push_back( 1 );          // LOCC_1
        aceified.push_back( 89 );         // LOCC_2
        // Reaction 1--MT16
        aceified.push_back( 47 );         // LNW_1
        aceified.push_back( 9 );          // LAW_1
        aceified.push_back( 12 );         // IDAT_1
        aceified.push_back( 0 );          // N_R
        aceified.push_back( 3 );          // N_E
        aceified |= ranges::action::push_back( energies_1 );
        aceified |= ranges::action::push_back( probabilities_1 );
          // LAW 9
          aceified.push_back( 0 );          // N_R
          aceified.push_back( 16 );          // N_E
          aceified |= ranges::action::push_back( Law9_1Energies );
          aceified |= ranges::action::push_back( Law9_1Theta ); 
          aceified.push_back( U_1 );
        aceified.push_back( 0 );          // LNW_2
        aceified.push_back( 9 );          // LAW_2
        aceified.push_back( 58 );         // IDAT_2
        aceified.push_back( 0 );          // N_R
        aceified.push_back( 3 );          // N_E
        aceified |= ranges::action::push_back( energies_1 );
        aceified |= ranges::action::push_back( probabilities_1 );
          // LAW 9
          aceified.push_back( 0 );          // N_R
          aceified.push_back( 14 );          // N_E
          aceified |= ranges::action::push_back( Law9_2Energies );
          aceified |= ranges::action::push_back( Law9_2Theta ); 
          aceified.push_back( U_2 );
        // Reaction 2--MT22
        aceified.push_back( 0 );         // LNW_1
        aceified.push_back( 9 );          // LAW_1
        aceified.push_back( 100 );         // IDAT_1
        aceified.push_back( 0 );          // N_R
        aceified.push_back( 3 );          // N_E
        aceified |= ranges::action::push_back( energies_2 );
        aceified |= ranges::action::push_back( probabilities_2 );
          // LAW 9
          aceified.push_back( 0 );          // N_R
          aceified.push_back( 10 );          // N_E
          aceified |= ranges::action::push_back( Law9_3Energies );
          aceified |= ranges::action::push_back( Law9_3Theta ); 
          aceified.push_back( U_3 );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 9 );                        // LAW_1
      aceified.push_back( 10 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( 2 );                        // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( theta );
      aceified.push_back( U );
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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 9 );                        // LAW_1
      aceified.push_back( 26 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( 1 );                        // N_R
      aceified |= ranges::action::push_back( boundaries );
      aceified |= ranges::action::push_back( schemes );
      aceified.push_back( 2 );                        // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( theta );
      aceified.push_back( U );
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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 9 );                        // LAW_1
      aceified.push_back( 44 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( 2 );                        // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( 1 );                        // N_R
      aceified |= ranges::action::push_back( boundaries );
      aceified |= ranges::action::push_back( schemes );
      aceified.push_back( 2 );                        // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( theta );
      aceified.push_back( U );
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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 62 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 73 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 84 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 95 );                       // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 106 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 117 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 128 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 139 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 150 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 161 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 0 );                        // LNW_1
      aceified.push_back( 3 );                        // LAW_1
      aceified.push_back( 172 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities );
      // LAW data
      aceified.push_back( Q );
      aceified.push_back( awr );

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

      aceified.push_back( 196 );                      // LNW_1
      aceified.push_back( 9 );                        // LAW_1
      aceified.push_back( 187 );                      // IDAT_1
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities_1 );
      // LAW data
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( law_energies.size() );      // N_E
      aceified |= ranges::action::push_back( law_energies );
      aceified |= ranges::action::push_back( theta );
      aceified.push_back( U_1 );
      //
      aceified.push_back( 0 );                        // LNW_2
      aceified.push_back( 9 );                        // LAW_2
      aceified.push_back( 209 );                      // IDAT_2
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( energies.size() );          // N_E
      aceified |= ranges::action::push_back( energies );
      aceified |= ranges::action::push_back( probabilities_2 );
      // LAW data
      aceified.push_back( 0 );                        // N_R
      aceified.push_back( law_energies.size() );      // N_E
      aceified |= ranges::action::push_back( law_energies );
      aceified |= ranges::action::push_back( theta );
      aceified.push_back( U_2 );

    }

    THEN( "the EnergyDistributions can be ACEified" ){

      Table::Data data{};
      int LED{ 1 };
      size_t NMT{ 15 };
      CENBuilder.ACEifyEDs( EDs, data, LED, NMT );
      
      auto& xss = data.XSS();
      CHECK( NMT == EDs.size() );
      CHECK( ranges::equal( aceified, xss ) );

    }
  }
} // SCENARIO
