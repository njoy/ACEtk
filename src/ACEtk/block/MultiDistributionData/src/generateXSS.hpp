static std::vector< double >
generateXSS( std::vector< DistributionProbability >&& probabilities,
             std::vector< DistributionData >&& distributions,
             std::size_t locb ) {

  std::vector< double > xss;
  std::size_t size = probabilities.size();
  if ( distributions.size() != size ) {

    Log::error( "The number of distributions and probabilities is not the same" );
    Log::info( "Found probabilities size = {}", size );
    Log::info( "Found distributions size = {}", distributions.size() );
    throw std::exception();
  }

  // add the probability and distribution pairs to the xss array
  // set lnw and idat appropriately
  for ( unsigned int i = 0; i < size; ++i ) {

    std::size_t offset = xss.size();
    xss.push_back( 0 ); // lnw
    std::visit(
        [ &xss ] ( const auto& value )
                 { xss.push_back( static_cast< double >( value.LAW() ) ); },
        distributions[i] );
    xss.push_back( 1 ); // idat
    xss.insert( xss.end(), probabilities[i].begin(), probabilities[i].end() );
    xss[ offset + 2 ] = xss.size() + locb; // idat
    std::visit(

      utility::overload{

        [ &xss, offset ] ( const KalbachMannDistributionData& value ) {

          // remake the internal xss array with the proper locators
          decltype(auto) boundaries = value.boundaries();
          decltype(auto) interpolants = value.interpolants();
          KalbachMannDistributionData temp(
              { boundaries.begin(), boundaries.end() },
              { interpolants.begin(), interpolants.end() },
              std::move( value.distributions() ),
              xss[ offset + 2 ] );
          xss.insert( xss.end(), temp.begin(), temp.end() );
        },
        [ &xss ] ( const auto& value ) {

          xss.insert( xss.end(), value.begin(), value.end() );
        }
      },
      distributions[i]
    );
    if ( i != size - 1 ) {

      xss[ offset ] = xss.size() + locb; // lnw
    }
  }

  return xss;
}
