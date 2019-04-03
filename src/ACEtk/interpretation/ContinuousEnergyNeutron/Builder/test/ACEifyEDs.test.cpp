
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

  std::vector< int > boundaries{ 0, 3 };
  std::vector< int > schemes{ 2, 1 };
  std::vector< double > energies{ 1.0, 2.0, 5.0, 6.0 };
  std::vector< double > probabilities{ 0.1, 0.2, 0.5, 0.2 };

  GIVEN( "valid inputs" ){
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
        ranges::view::single( 0 ),          // LOCC_2
        // First set of distributions
          ranges::view::single( 0 ),        // LNW_1
          ranges::view::single( 2 ),        // LAW_1
          ranges::view::single( 14 ),       // IDAT_1
          ranges::view::single( 2 ),        // N_R_1
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_1
          energies, probabilities,
          // Discrete photon energy
            ranges::vew::single( 3.14 ),
            ranges::vew::single( 1 ),

          ranges::view::single( 0 ),        // LNW_2
          ranges::view::single( 2 ),        // LAW_2
          ranges::view::single( 14 ),       // IDAT_2
          ranges::view::single( 2 ),        // N_R_2
          boundaries, schemes,
          ranges::view::single( 4 ),        // N_E_2
          energies, probabilities,
          // Level scattering
            ranges::vew::single( 235.98 ),
            ranges::vew::single( 2.765 ),

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
} // SCENARIO
