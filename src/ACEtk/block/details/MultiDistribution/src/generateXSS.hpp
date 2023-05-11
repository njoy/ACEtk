static std::vector< double >
generateXSS( std::vector< DistributionProbability >&& probabilities,
             std::vector< DistributionData >&& distributions,
             std::size_t locb ) {

  std::vector< double > xss;
  const auto size = probabilities.size();
  if ( distributions.size() != size ) {

    Log::error( "The number of distributions and probabilities is not the same" );
    Log::info( "Found probabilities size = {}", size );
    Log::info( "Found distributions size = {}", distributions.size() );
    throw std::exception();
  }

  // add the probability and distribution pairs to the xss array
  // set lnw and idat appropriately
  for ( unsigned int i = 0; i < size; ++i ) {

    const auto offset = xss.size();
    xss.push_back( 0 ); // lnw
    xss.push_back( static_cast< double >( Derived::retrieveLAW( distributions[i] ) ) ); // law
    xss.push_back( 1. ); // idat
    xss.insert( xss.end(), probabilities[i].begin(), probabilities[i].end() );
    xss[ offset + 2 ] = static_cast< double >( xss.size() + locb ); // idat

    Derived::insertXSS( xss, distributions[i] );
    if ( i != size - 1 ) {

      xss[ offset ] = xss.size() + locb; // lnw
    }
  }

  return xss;
}
