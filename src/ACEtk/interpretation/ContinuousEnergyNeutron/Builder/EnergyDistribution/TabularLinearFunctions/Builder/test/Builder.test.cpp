#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ACEtk.hpp"

using namespace njoy::ACEtk;
using namespace njoy::ACEtk::interpretation;

SCENARIO( "Testing EnergyDistribtion::TabularLinearFunctions::Builder" ){
    ContinuousEnergyNeutron::Builder CENBuilder;

    auto parentBuilder = CENBuilder.reaction( 14 ).energyDistribution();
    using TLFBuilder = decltype( parentBuilder.tabularLinearFunctions() );

    struct TestBuilder : public TLFBuilder {
      using TLFBuilder::construct;
      using TLFBuilder::TLFBuilder;
    };

  TestBuilder tLF( parentBuilder );

  GIVEN( "valid inputs" ){
    std::vector< int > boundaries{ 1, 3 };
    std::vector< int > schemes{ 2, 1 };
    std::vector< double > energies{ 1.0, 2.0 };

    tLF.boundaries( njoy::utility::copy( boundaries ) )
       .schemes( njoy::utility::copy( schemes ) )
       .energies( njoy::utility::copy( energies ) );

    std::vector< double > P{ 0.1, 0.2, 0.4 };
    std::vector< double > T{ 1.1, 1.2, 1.4 };
    std::vector< double > C{ 2.1, 2.2, 2.4 };

    tLF.distributionData().P( njoy::utility::copy( P ) )
                          .T( njoy::utility::copy( T ) )
                          .C( njoy::utility::copy( C ) )
       .add()
       .distributionData().P( njoy::utility::copy( P ) )
                          .T( njoy::utility::copy( T ) )
                          .C( njoy::utility::copy( C ) )
       .add();

    auto distribution = tLF.construct();

    THEN( "the values can be verified" ){
      auto tab = distribution.tabulated;
      auto parameters = tab.parameters;
      CHECK( ranges::equal( boundaries, parameters->first ) );
      CHECK( ranges::equal( schemes, parameters->second ) );
      CHECK( ranges::equal( energies, tab.x ) );

      auto y = tab.y;
      CHECK( 2 == y.size() );

      AND_THEN( "the contents can be ACE-ified" ){
        std::vector< double > aceified{};
        aceified.push_back( boundaries.size() );
        aceified |= ranges::action::push_back( boundaries );
        aceified |= ranges::action::push_back( schemes );
        aceified.push_back( energies.size() );
        aceified |= ranges::action::push_back( energies );
        aceified.push_back( 11 ); // LOCE_1
        aceified.push_back( 21 ); // LOCE_2
          // Data_1
          aceified.push_back( P.size() );
          aceified |= ranges::action::push_back( P );
          aceified |= ranges::action::push_back( T );
          aceified |= ranges::action::push_back( C );
          // Data_2
          aceified.push_back( P.size() );
          aceified |= ranges::action::push_back( P );
          aceified |= ranges::action::push_back( T );
          aceified |= ranges::action::push_back( C );

        Table::Data data{};
        distribution.ACEify( data, 0 );

        CHECK( ranges::equal( aceified, data.XSS() ) );
      }
    }

  } // GIVEN valid
  GIVEN( "invalid inputs" ){
    WHEN( "energies are negative" ){
      std::vector< double > energies{ -1.0, 2.0, 5.0, 6.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tLF.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::NotPositive&
        );
      }
    }
    WHEN( "energies are not sorted" ){
      std::vector< double > energies{ 1.0, 2.0, 5.0, 4.0 };

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( 
          tLF.energies( njoy::utility::copy( energies ) ),
          details::verify::exceptions::Unsorted&
        );
      }
    }
    WHEN( "not enough Data members" ){
      std::vector< int > boundaries{ 1, 3 };
      std::vector< int > schemes{ 2, 1 };
      std::vector< double > energies{ 1.0, 2.0 };

      tLF.boundaries( njoy::utility::copy( boundaries ) )
        .schemes( njoy::utility::copy( schemes ) )
        .energies( njoy::utility::copy( energies ) );

      std::vector< double > P{ 0.1, 0.2, 0.4 };
      std::vector< double > T{ 1.1, 1.2, 1.4 };
      std::vector< double > C{ 2.1, 2.2, 2.4 };

      tLF.distributionData().P( njoy::utility::copy( P ) )
                            .T( njoy::utility::copy( T ) )
                            .C( njoy::utility::copy( C ) )
        .add();

      THEN( "an exception is thrown" ){
        CHECK_THROWS_AS( tLF.construct(), std::range_error& );
      }
    }
  }
} // SCENARIO
