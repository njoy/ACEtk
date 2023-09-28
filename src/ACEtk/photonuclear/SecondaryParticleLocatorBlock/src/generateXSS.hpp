static std::vector< double >
generateXSS( std::vector< unsigned int >&& types,
             std::vector< unsigned int >&& numbers,
             std::vector< std::array< unsigned int, 10 > >&& locators ) {

  std::vector< double > xss;
  const auto ntype = locators.size();
  xss.reserve( ntype * 12 );

  if ( ( types.size() != ntype ) || ( numbers.size() != ntype ) ) {

    Log::error( "The number of particles is not consistent between the particle types, "
                "the number of reactions and the locator sets" );
    Log::info( "Expected: {}", ntype );
    Log::info( "Found types: {}", types.size() );
    Log::info( "Found numbers: {}", numbers.size() );
    Log::info( "Found locators: {}", locators.size() );
    throw std::exception();
  }

  for ( unsigned int index = 0; index < ntype; ++index ) {

    xss.push_back( static_cast< double >( types[index] ) );
    xss.push_back( static_cast< double >( numbers[index] ) );
    xss.insert( xss.end(), locators[index].begin(), locators[index].end() );
  }
  return xss;
}
